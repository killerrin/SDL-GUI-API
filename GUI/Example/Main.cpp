#include "Client.h"
using namespace Example;

int main(int argc, char* argcs[]) {
	Client* client = Client::GetInstance();
	client->Run();
	delete client;

	return 0;
}