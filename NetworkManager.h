#pragma once
#include "Constants.h"

class NetworkManager
{
private:
	sf::TcpSocket socket;

public:
	NetworkManager();
	~NetworkManager();

	bool ConnectToServer();
	void SendHandshake();
	void ReceiveData();

	friend sf::Packet& operator>>(sf::Packet& packet, packetType& type);

};