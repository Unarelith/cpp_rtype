/*
 * =====================================================================================
 *
 *       Filename:  TestBulletFactory.cpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:25:09
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <cmath>

#include <SFML/Network.hpp>

#include "Application.hpp"
#include "EasyMovement.hpp"
#include "HitboxComponent.hpp"
#include "Image.hpp"
#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "TestBulletFactory.hpp"

SceneObject TestBulletFactory::create(const std::string &textureName, const sf::Vector2f &pos, const sf::Vector2f &v) {
	SceneObject object{"BasicBullet", "Bullet"};
	object.set<LifetimeComponent>(&TestBulletFactory::checkOutOfMap);
	object.set<MovementComponent>(new EasyMovement([v] (const SceneObject &object) {
		object.get<MovementComponent>().v = v;
	})).speed = 3.0f;

	auto &image = object.set<Image>(textureName);
	object.set<HitboxComponent>(0, 0, image.width(), image.height());

	object.setPosition(pos);

	return object;
}

SceneObject TestBulletFactory::createClient(const std::string &name, const std::string &textureName, const sf::Vector2f &pos) {
	SceneObject object{name, "Bullet"};
	object.set<Image>(textureName);
	object.setPosition(pos);

	return object;
}

SceneObject TestBulletFactory::createServer(const std::string &textureName, const sf::Vector2f &pos, const sf::Vector2f &v) {
	static size_t bulletCount = 0;
	SceneObject object{"BasicBullet" + std::to_string(bulletCount++), "Bullet"};
	object.set<LifetimeComponent>(&TestBulletFactory::checkOutOfMap);
	object.set<MovementComponent>(new EasyMovement([v] (const SceneObject &object) {
		object.get<MovementComponent>().v = v;
	})).speed = 3.0f;

	sf::UdpSocket &socket = object.set<sf::UdpSocket>();
	socket.bind(0);

	sf::Packet packet;
	packet << "BulletSpawn" << object.name() << object.type() << socket.getLocalPort() << textureName << object.getPosition().x << object.getPosition().y;
	socket.send(packet, sf::IpAddress::Any, 4243);

	// auto &image = object.set<Image>(textureName);
	// object.set<HitboxComponent>(0, 0, image.width(), image.height());

	// FIXME: WARNING HARDCODED SIZE
	object.set<HitboxComponent>(0, 0, 16, 8);

	object.setPosition(pos);

	return object;
}

bool TestBulletFactory::checkOutOfMap(const SceneObject &object) {
	return (object.getPosition().x + object.get<HitboxComponent>().currentHitbox()->width < 0 ||
	        object.getPosition().x > Application::screenWidth ||
	        object.getPosition().y + object.get<HitboxComponent>().currentHitbox()->height < 0 ||
	        object.getPosition().y > Application::screenHeight);
}

