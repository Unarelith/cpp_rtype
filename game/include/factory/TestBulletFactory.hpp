/*
 * =====================================================================================
 *
 *       Filename:  TestBulletFactory.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:22:21
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TESTBULLETFACTORY_HPP_
#define TESTBULLETFACTORY_HPP_

#include <gk/core/Vector2.hpp>
#include <gk/scene/SceneObject.hpp>

class TestBulletFactory {
	public:
		static gk::SceneObject create(const std::string &type, const std::string &textureName, const gk::Vector2f &pos, const gk::Vector2f &v, float speed);

	private:
		static bool checkOutOfMap(const gk::SceneObject &object);
};

#endif // TESTBULLETFACTORY_HPP_
