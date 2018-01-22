/*
 * =====================================================================================
 *
 *       Filename:  TestEnemyFactory.cpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 05:38:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "BehaviourComponent.hpp"
#include "EasyBehaviour.hpp"
#include "EasyMovement.hpp"
#include "HealthComponent.hpp"
#include "HitboxComponent.hpp"
#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "SceneObjectList.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"
#include "TestEnemyFactory.hpp"

SceneObject TestEnemyFactory::create(const sf::Vector2f &pos) {
	static size_t enemyCount = 0;
	SceneObject object{"TestEnemy" + std::to_string(enemyCount++), "Enemy"};
	object.setPosition(pos);
	object.set<NetworkComponent>();
	object.set<SceneObjectList>();
	object.set<Timer>().start();
	object.set<HealthComponent>(500);
	object.set<LifetimeComponent>([&] (const SceneObject &object) {
		return checkOutOfMap(object) || object.get<HealthComponent>().life() == 0;
	});

	object.set<MovementComponent>(new EasyMovement([] (SceneObject &object) {
		object.get<MovementComponent>().v.x = -1;
	})).speed = 0.8f;

	auto &spriteComponent = object.set<SpriteComponent>("characters-enemy1", 33, 33);
	object.set<HitboxComponent>(0, 0, spriteComponent.frameWidth(), spriteComponent.frameHeight());

	auto &collisionComponent = object.set<CollisionComponent>();
	collisionComponent.addAction(&TestEnemyFactory::enemyCollisionAction);

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [] (SceneObject &object) {
		Timer &timer = object.get<Timer>();
		if (timer.time() > 1000) {
			sf::Vector2f bulletPosition = object.getPosition() + sf::Vector2f{0, (float)object.get<HitboxComponent>().currentHitbox()->height / 2 - 4};
			object.get<SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullets-small", bulletPosition, {-1, 0}));

			timer.reset();
			timer.start();
		}
	});

	return object;
}

void TestEnemyFactory::enemyCollisionAction(SceneObject &enemy, SceneObject &object, bool inCollision) {
	// FIXME: WARNING NAME CHECK
	if (inCollision && object.type() == "PlayerBullet"
	 && !enemy.get<LifetimeComponent>().dead(enemy)
	 && !object.get<LifetimeComponent>().dead(object)) {
		// TODO: Create BulletComponent with damage
		enemy.get<HealthComponent>().removeLife(100);
		object.get<LifetimeComponent>().kill();
	}
}

bool TestEnemyFactory::checkOutOfMap(const SceneObject &object) {
	return (object.getPosition().x + object.get<HitboxComponent>().currentHitbox()->width < 0 ||
	        object.getPosition().y + object.get<HitboxComponent>().currentHitbox()->height < 0);
}

