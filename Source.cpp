#include "NetworkManager.h"
#include <iostream>

void main() {
	NetworkManager networkManager;

	if (networkManager.ConnectToServer()) {

		networkManager.ReceiveData();

		// Boton de mentirijilla
		networkManager.SendRegister("Chuchulia", "AAAAAAAAAA<3");
	}

	// Para que el cliente no muera:
	std::cout << "Esperando respuesta del servidor... (Pulsa Enter para salir)" << std::endl;
	std::cin.get(); // O system("pause");
}