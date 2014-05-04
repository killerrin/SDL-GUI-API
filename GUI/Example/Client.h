#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "ClientSettings.h"

//-- Load the GUI Functions
#include "GUI.h"
#include "ScreenFader.h"

//-- Load Menus
#include "MainMenu.h"

namespace Example {
	class Client {
	protected:
		Client();

		//-- Pages Here
		MainMenu* mainMenu;

	public:
		static Client* GetInstance() {
			if (instance == nullptr) {
				instance = new Client();
			}

			return instance;
		}

		~Client();

		ClientSettings* Settings() { return settings; }

		void Run();

	private:
		static Client* instance;
		ClientSettings* settings;

		void LoadContent();

		static void Update(double time);
		static void Draw();
		static void OnEscapePressed();
		static void OnEnterPressed();
	};
}
#endif