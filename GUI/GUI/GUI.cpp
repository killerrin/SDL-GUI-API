#include "GUI.h"
using namespace GuiAPI;

#pragma region Private Variable Initalizations
std::map<std::string, TTF_Font*> GUI::fonts;
std::map<std::string, SDL_Texture*> GUI::textures;
std::map<std::string, Mix_Chunk*> GUI::audio;
std::map<std::string, SDL_Color> GUI::colours;
std::map<std::string, SDL_Rect> GUI::rects;

//-- API Objects
std::map<std::string, Container*> GUI::guiContainers;
std::map<std::string, Element*> GUI::guiElements;

void (*GUI::CustomUpdateFunc)(double);
void (*GUI::CustomDrawFunc)();
void(*GUI::EnterKeyPressedFunc)();
void(*GUI::EscapeKeyPressedFunc)();

Page* GUI::focus;
FrameLimiter* GUI::frameLimiter;
APIMode GUI::GuiAPIMode;

bool GUI::quit;
#pragma endregion

void GUI::BeginMainLoop()
{
	// Initialize quit to false so that the loop will run indefinately
	quit = false;

	//Pre-Draw screen before entering loop
	Draw();

	//-- Begin Main Loop
	while (!quit)
	{
		if (!frameLimiter->Limit()) {
			Update(frameLimiter->GetFPS());
			Draw();
		}
	}
}

void GUI::Update(double time)
{
	CheckEvents();

	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
#pragma region Update All Elements
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			it->second->Update(time);
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			it->second->Update(time);
		}
#pragma endregion
		break;
	case APIMode::FocusMode:
		focus->Update(time);
		break;
	}


	//-- Run Custom Update if it exists
	if (CustomUpdateFunc != NULL) { (*CustomUpdateFunc)(time); }
}
void GUI::Draw()
{
	Window::Clear();

	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
#pragma region Draw All Elements
		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			it->second->Draw();
		}

		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			it->second->Draw();
		}
#pragma endregion
		break;
	case APIMode::FocusMode:
		focus->Draw();
		break;
	}

	//-- Run Custom Update if it exists
	if (CustomDrawFunc != NULL) { (*CustomDrawFunc)(); }

	Window::Present();
}
void GUI::CheckEvents()
{
	APIEvents::CurrentKeyboardState = SDL_GetKeyboardState(NULL);
	APIEvents::CurrentMouseState = SDL_GetMouseState(NULL,NULL);

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			ExitMainLoop();
		if (event.type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&APIEvents::MousePosition.x, &APIEvents::MousePosition.y);

		// Begin Event Code
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			HandleMouseMotionEvent(event.motion);
			break;
		case SDL_MOUSEBUTTONDOWN:
			HandleMouseDownEvent(event.button);
			break;
		case SDL_MOUSEBUTTONUP:
			HandleMouseUpEvent(event.button);
			break;
		case SDL_TEXTINPUT:
			HandleTextInputEvent(event.text);
			break;
		case SDL_KEYDOWN:
			HandleKeyboardDownEvent(event.key);
			break;
		case SDL_KEYUP:
			HandleKeyboardUpEvent(event.key);
			break;
		}
	}

	if (APIEvents::DidMouseClick()) {
			HandleMouseClickEvent();
	}

	if (GUIHelper::DidKeyGetPressed(SDL_SCANCODE_RETURN)) {

	}

	APIEvents::PreviousKeyboardState = APIEvents::CurrentKeyboardState;
	APIEvents::PreviousMouseState = APIEvents::CurrentMouseState;
}

void GUI::HandleMouseMotionEvent(SDL_MouseMotionEvent e)
{
	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnMouseMotion(e);
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnMouseMotion(e);
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnMouseMotion(e);
		break;
	}
	
}
void GUI::HandleMouseDownEvent(SDL_MouseButtonEvent e)
{
	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnMouseDown(e);
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				if (it->second->Intersects(APIEvents::MousePosition))
					it->second->OnMouseDown(e);
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnMouseDown(e);
		break;
	}

}
void GUI::HandleMouseUpEvent(SDL_MouseButtonEvent e)
{
	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnMouseUp(e);
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnMouseUp(e);
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnMouseUp(e);
		break;
	}

}
void GUI::HandleMouseClickEvent()
{
	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnMouseClick();
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				if (it->second->Intersects(APIEvents::MousePosition))
					it->second->OnMouseClick();
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnMouseClick();
		break;
	}
	
}

void GUI::HandleTextInputEvent(SDL_TextInputEvent e)
{
	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnTextInput(e);
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnTextInput(e);
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnTextInput(e);
		break;
	}
	
}
void GUI::HandleKeyboardDownEvent(SDL_KeyboardEvent e)
{
	if (e.keysym.sym == SDLK_RETURN ||
		e.keysym.sym == SDLK_RETURN2 ||
		e.keysym.sym == SDLK_KP_ENTER) 
	{
		HandleEnterKeyPressed();
	}

	if (e.keysym.sym == SDLK_ESCAPE)
	{
		HandleEscapeKeyPressed();
	}

	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnKeyboardDown(e);
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnKeyboardDown(e);
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnKeyboardDown(e);
		break;
	}
	
}
void GUI::HandleKeyboardUpEvent(SDL_KeyboardEvent e)
{
	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnKeyboardUp(e);
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnKeyboardUp(e);
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnKeyboardUp(e);
		break;
	}
}
void GUI::HandleEnterKeyPressed()
{
	APIEvents::EnterPressed = !APIEvents::EnterPressed;

	if (EnterKeyPressedFunc != NULL) {
		(*EnterKeyPressedFunc)();
	}

	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnEnterKeyPressed();
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnEnterKeyPressed();
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnEnterKeyPressed();
		break;
	}
}
void GUI::HandleEscapeKeyPressed()
{
	APIEvents::EscapePressed = !APIEvents::EscapePressed;

	if (EscapeKeyPressedFunc != NULL) {
		(*EscapeKeyPressedFunc)();
	}

	switch (GUI::GuiAPIMode)
	{
	default:
	case APIMode::APIHandleMode:
		for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnEscapeKeyPressed();
			}
		}

		for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
		{
			if (it->second->Active) {
				it->second->OnEscapeKeyPressed();
			}
		}
		break;
	case APIMode::FocusMode:
		focus->OnEscapeKeyPressed();
		break;
	}
}