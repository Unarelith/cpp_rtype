/*
 * =====================================================================================
 *
 *       Filename:  TestEntityFactory.hpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:36:44
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TESTENTITYFACTORY_HPP_
#define TESTENTITYFACTORY_HPP_

#include "SceneObject.hpp"

class TestEntityFactory {
	public:
		static SceneObject create(u16 x, u16 y);
};

#endif // TESTENTITYFACTORY_HPP_