/*
 * =====================================================================================
 *
 *       Filename:  LifetimeComponent.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 04:13:13
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef LIFETIMECOMPONENT_HPP_
#define LIFETIMECOMPONENT_HPP_

#include <functional>

#include "SceneObject.hpp"
#include "Timer.hpp"

class LifetimeComponent {
	using DeathChecker = std::function<bool(const SceneObject &)>;

	public:
		LifetimeComponent() = default;
		LifetimeComponent(u32 lifetime) : m_lifetime(lifetime) { m_timer.start(); }
		LifetimeComponent(DeathChecker deathChecker) : m_deathChecker(deathChecker) {}

		void kill() { m_dead = true; }

		bool almostDead() { return m_lifetime != 0 && m_timer.time() > m_lifetime / 4 * 3; }

		bool dead(const SceneObject &object) const {
			return m_dead
				|| (m_lifetime != 0 && m_timer.time() > m_lifetime)
				|| (m_deathChecker && m_deathChecker(object));
		}

		u32 aliveTime() { return m_timer.time(); }

		bool areClientsNotified() const { return m_areClientsNotified; }

		void setDeathChecker(DeathChecker deathChecker) { m_deathChecker = deathChecker; }
		void setClientsNotified(bool areClientsNotified) { m_areClientsNotified = areClientsNotified; }

	private:
		Timer m_timer;

		bool m_dead = false;
		bool m_areClientsNotified = false;

		u32 m_lifetime = 0;

		DeathChecker m_deathChecker;
};

#endif // LIFETIMECOMPONENT_HPP_
