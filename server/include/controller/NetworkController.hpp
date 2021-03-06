/*
 * =====================================================================================
 *
 *       Filename:  NetworkController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:21:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORKCONTROLLER_HPP_
#define NETWORKCONTROLLER_HPP_

#include <SFML/Network/UdpSocket.hpp>

#include <gk/scene/controller/AbstractController.hpp>

#include "ServerInfo.hpp"

class NetworkController : public gk::AbstractController {
	public:
		NetworkController(ServerInfo &serverInfo, sf::UdpSocket &socket)
			: m_serverInfo(serverInfo), m_socket(socket) {}

		void update(gk::SceneObject &object) override;

	private:
		ServerInfo &m_serverInfo;

		sf::UdpSocket &m_socket;
};

#endif // NETWORKCONTROLLER_HPP_
