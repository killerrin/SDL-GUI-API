#include "ClientSettings.h"
using namespace Example;

//std::string ClientSettings::Username;
ClientSettings* ClientSettings::instance;

ClientSettings::ClientSettings()
{
	Username = "";
	loggedIn = false;
	isHost = false;
}

ClientSettings* ClientSettings::GetInstance()
{
	if (instance == nullptr) { instance = new ClientSettings(); }
	return instance;
}

ClientSettings::~ClientSettings()
{
}
