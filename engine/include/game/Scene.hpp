/*
 * =====================================================================================
 *
 *       Filename:  Scene.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:34:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <list>
#include <functional>

#include <SFML/Graphics/Drawable.hpp>

#include "AbstractController.hpp"
#include "AbstractView.hpp"
#include "SceneObject.hpp"
#include "SceneObjectList.hpp"

class Scene : public sf::Drawable {
	public:
		void reset();
		void update();

		SceneObject &addObject(SceneObject &&object);

		void addCollisionChecker(std::function<void(SceneObject &)> checker);
		void checkCollisionsFor(SceneObject &object);

		SceneObjectList &objects() { return m_objects; }
		const SceneObjectList &objects() const { return m_objects; }

		void addController(AbstractController *controller) { m_controllerList.emplace_back(controller); }
		void addView(AbstractView *view) { m_viewList.emplace_back(view); }

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		SceneObjectList m_objects;

		std::list<std::unique_ptr<AbstractController>> m_controllerList;
		std::list<std::unique_ptr<AbstractView>> m_viewList;
};

#endif // SCENE_HPP_
