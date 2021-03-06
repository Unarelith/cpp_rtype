/*
 * =====================================================================================
 *
 *       Filename:  BossFactory.hpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 00:32:38
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef BOSSFACTORY_HPP_
#define BOSSFACTORY_HPP_

#include <gk/scene/component/CollisionComponent.hpp>
#include <gk/scene/SceneObject.hpp>

class BossFactory {
	public:
		static gk::SceneObject create();

	private:
		static void bossCollisionAction(gk::SceneObject &enemy, gk::SceneObject &object, bool inCollision);

		// static bool checkOutOfMap(const SceneObject &object);
};

#endif // BOSSFACTORY_HPP_
