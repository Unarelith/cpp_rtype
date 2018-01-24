/*
 * =====================================================================================
 *
 *       Filename:  DrawingSystem.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:49:51
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "DrawingSystem.hpp"
#include "Image.hpp"
#include "LifetimeComponent.hpp"
#include "PositionComponent.hpp"
#include "Sprite.hpp"

void DrawingSystem::draw(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states) {
	if (object.has<LifetimeComponent>() && object.get<LifetimeComponent>().dead(object))
		return;

	if (object.has<PositionComponent>())
		states.transform.translate(object.get<PositionComponent>());

	if(object.has<Image>()) {
		target.draw(object.get<Image>(), states);
	}

	if(object.has<Sprite>()) {
		target.draw(object.get<Sprite>(), states);
	}
}
