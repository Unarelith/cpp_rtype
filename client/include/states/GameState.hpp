/*
 * =====================================================================================
 *
 *       Filename:  GameState.hpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:44:55
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <SFML/Network/IpAddress.hpp>

#include "ApplicationState.hpp"
#include "Image.hpp"
#include "Scene.hpp"

class GameState : public ApplicationState {
	public:
		GameState(const sf::IpAddress &serverAddress, u16 serverPort = 4243);

		void onEvent(sf::Event &event) override;

		void update() override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		Image m_background{"background-space"};

		Scene m_scene;
};

#endif // GAMESTATE_HPP_
