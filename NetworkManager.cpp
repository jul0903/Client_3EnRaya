#include <iostream>
#include "NetworkManager.h"

// Sobrecargar operador
sf::Packet& operator>>(sf::Packet& packet, packetType& type) {
	int temp;
	packet >> temp;
	type = static_cast<packetType>(temp);

	return packet;
}

NetworkManager::NetworkManager()
{
	// Constructor
}

NetworkManager::~NetworkManager()
{
	socket.disconnect();
}

bool NetworkManager::ConnectToServer()
{
	if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
		std::cerr << "Error al conectar con el servidor" << std::endl;

		return false;
	}

	std::cout << "Conectado al servidor :)" << std::endl;
	return true;
}

void HandShake(sf::Packet data) {
	std::string message;
	data >> message;

	std::cout << "Mensaje recibido del servidor: " << message << std::endl;
}

void NetworkManager::SendHandshake()
{
	sf::Packet packet;
}

void NetworkManager::ReceiveData()
{
	sf::Packet packet;

	// Receive info
	if (socket.receive(packet) == sf::Socket::Status::Done) {

		packetType type;
		packet >> type;

		switch (type) {
		case packetType::HANDSHAKE:
			HandShake(packet);
			break;
		case packetType::LOGIN:
			break;
		case packetType::MOVIMIENTO:
			break;
		}

		packet.clear();

	}
	else {
		std::cerr << "Error al recibir el mensaje del servidor" << std::endl;
	}
}
