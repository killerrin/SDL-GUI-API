#pragma once
#ifndef API_EVENTS_H
#define API_EVENTS_H

#include "SDLIncludes.h"

namespace GuiAPI {
	class APIEvents
	{
	public:
		static SDL_Event Event;

		static const Uint8 *CurrentKeyboardState;
		static const Uint8 *PreviousKeyboardState;

		static Uint32 CurrentMouseState;
		static Uint32 PreviousMouseState;

		static SDL_Rect MousePosition;

		static bool EnterPressed;
		static bool EscapePressed;

		static bool SDLTextInputEnabled;

		static bool DidKeyGetPressed(SDL_Scancode key) { return ((CurrentKeyboardState[key] != SDL_PRESSED) && (PreviousKeyboardState[key] == SDL_PRESSED)); }
		static bool DidMouseClick() { return ((CurrentMouseState == SDL_PRESSED) && (PreviousMouseState != SDL_PRESSED)); }
	};
}
#endif