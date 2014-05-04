#pragma once
#ifndef CLIENT_SETTINGS_H
#define CLIENT_SETTINGS_H

#include <string>
#include <vector>
#include "Gamestate.h"

namespace Example {
	class ClientSettings
	{
	private:
		static ClientSettings* instance;

	protected:
		ClientSettings();

	public:
		static ClientSettings* GetInstance();
		~ClientSettings();

		Gamestate GameState = GS_None;

		std::string Username;
		bool loggedIn;
		bool isHost;
	};
}

#endif