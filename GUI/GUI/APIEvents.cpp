#include "APIEvents.h"
using namespace GuiAPI;

SDL_Event APIEvents::Event;

const Uint8 *APIEvents::CurrentKeyboardState;
const Uint8 *APIEvents::PreviousKeyboardState;

Uint32 APIEvents::CurrentMouseState;
Uint32 APIEvents::PreviousMouseState;

bool APIEvents::EnterPressed;
bool APIEvents::EscapePressed;
bool APIEvents::SDLTextInputEnabled;

SDL_Rect APIEvents::MousePosition;