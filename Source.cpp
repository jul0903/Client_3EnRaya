#include <iostream>
#include "Constants.h"

enum tipoPaquete { HANDSHAKE, LOGIN, MOVIMIENTO };

// Sobrecargar operador
sf::Packet& operator>>(sf::Packet& packet, tipoPaquete& tipo) {
	int temp;
	packet >> temp;
	tipo = static_cast<tipoPaquete>(temp);

	return packet;
}

void HandShake(sf::Packet data) {
	std::string message;
	data >> message;

	std::cout << "Mensaje recibido del servidor: " << message << std::endl;
}

void main() {
	sf::TcpSocket socket;

	//Conexion
	if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
		std::cerr << "Error al conectar con el servidor" << std::endl;
	}

	std::cout << "Conectado al servidor" << std::endl;

	sf::Packet packet;

	// Receive info
	if (socket.receive(packet) == sf::Socket::Status::Done) {

		tipoPaquete tipo;
		packet >> tipo;

		switch (tipo) {
		case HANDSHAKE:
			HandShake(packet);
			break;
		case LOGIN:
			break;
		case MOVIMIENTO:
			break;
		}

		packet.clear();

	}
	else {
		std::cerr << "Error al recibir el mensaje del servidor" << std::endl;
	}
}