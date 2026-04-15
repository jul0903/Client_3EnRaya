#include <iostream>
#include "NetworkManager.h"

// Sobrecargar operador
// Empaquetar
sf::Packet& operator<<(sf::Packet& packet, packetType type) {
	packet << static_cast<int>(type);
	return packet;
}

// Desempaquetar
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
		case packetType::REGISTER:
			break;
		}

		packet.clear();

	}
	else {
		std::cerr << "Error al recibir el mensaje del servidor" << std::endl;
	}
}

void NetworkManager::SendRegister(std::string username, std::string password)
{
	sf::Packet packet;

	// Empaquetamos en orden: 1.Type, 2.User, 3.Password
	packet << packetType::REGISTER << username << password;

	if (socket.send(packet) == sf::Socket::Status::Done) {
		std::cout << "Datos del usuario: " << username << " enviados al servidor" << std::endl;
	}
	else {
		std::cout << "Error al enviar los datos" << std::endl;
	}
}