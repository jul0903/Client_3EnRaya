#include "NetworkManager.h"

void main() {
	NetworkManager networkManager;

	if (networkManager.ConnectToServer()) {

		networkManager.ReceiveData();
	}
}