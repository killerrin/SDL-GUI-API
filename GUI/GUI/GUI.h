#pragma once
#ifndef CLIENT_API_H
#define CLIENT_API_H

#include "SDLIncludes.h"
#include "GUIHelper.h"
#include "APIEvents.h"
#include "APIMode.h"

#include "Page.h"

#include "FrameLimiter.h"
#include "Window.h"
#include "Container.h"
#include "Element.h"
#include "Button.h"
#include "Label.h"
#include "TextField.h"
#include "Checkbox.h"
#include "Slider.h"

//class Page;

namespace GuiAPI {
	class GUI
	{
	private:
#pragma region Resources
		//-- Fonts, Textures & Colours

		static std::map<std::string, TTF_Font*> fonts;

		static std::map<std::string, SDL_Texture*> textures;

		static std::map<std::string, Mix_Chunk*> audio;

		static std::map<std::string, SDL_Color> colours;

		static std::map<std::string, SDL_Rect> rects;

		//-- API Objects
		static std::map<std::string, Container*> guiContainers;

		static std::map<std::string, Element*> guiElements;

		static bool quit;

		static Page* focus;
		static FrameLimiter* frameLimiter;
		static APIMode GuiAPIMode;

		static void(*CustomUpdateFunc)(double);
		static void(*CustomDrawFunc)();
		static void(*EnterKeyPressedFunc)();
		static void(*EscapeKeyPressedFunc)();

		static void SetupHelper(){
			fonts = std::map < std::string, TTF_Font* > {};
			textures = std::map < std::string, SDL_Texture* > {};
			audio = std::map < std::string, Mix_Chunk* > {};
			colours = std::map < std::string, SDL_Color > {};
			rects = std::map < std::string, SDL_Rect > {};

			guiContainers = std::map < std::string, Container* > {};
			guiElements = std::map < std::string, Element* > {};

			CustomUpdateFunc = nullptr;
			CustomDrawFunc = nullptr;
			EnterKeyPressedFunc = nullptr;
			EscapeKeyPressedFunc = nullptr;

			APIEvents::PreviousKeyboardState = SDL_GetKeyboardState(NULL);
			APIEvents::PreviousMouseState = SDL_GetMouseState(NULL, NULL);
			APIEvents::MousePosition = { -2, -2, 1, 1 };
			APIEvents::EnterPressed = false;
			APIEvents::EscapePressed = false;
			APIEvents::SDLTextInputEnabled = false;

			GUIHelper::ToggleTextInput();
		}
		static void CleanMemory()
		{
			for (std::map<std::string, TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it)
			{
				TTF_CloseFont(it->second);
			}
			fonts.clear();

			for (std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
			{
				SDL_DestroyTexture(it->second);
			}
			textures.clear();

			for (std::map<std::string, Mix_Chunk*>::iterator it = audio.begin(); it != audio.end(); ++it)
			{
				Mix_FreeChunk(it->second);
			}
			audio.clear();

			colours.clear();

			rects.clear();

			guiElements.clear();

			delete frameLimiter;
		}

		static void HandleMouseMotionEvent(SDL_MouseMotionEvent e);
		static void HandleMouseClickEvent();
		static void HandleMouseDownEvent(SDL_MouseButtonEvent e);
		static void HandleMouseUpEvent(SDL_MouseButtonEvent e);

		static void HandleKeyboardDownEvent(SDL_KeyboardEvent e);
		static void HandleKeyboardUpEvent(SDL_KeyboardEvent e);
		static void HandleEnterKeyPressed();
		static void HandleEscapeKeyPressed();
		static void HandleTextInputEvent(SDL_TextInputEvent e);
#pragma endregion

		static void CheckEvents();
		static void Update(double time);
		static void Draw();
	public:
		static void Init(std::string title = "Window", int FPS = 30, int width = 1024, int height = 768)
		{
			Window::Init(title, width, height);

			frameLimiter = new FrameLimiter(FPS);
			GuiAPIMode = APIMode::APIHandleMode;

			SetupHelper();
		};
		static void Exit() { Quit(); };
		static void Quit()
		{
			CleanMemory();
			GUIHelper::ToggleTextInput();
			Window::Quit();
		};

		static void SetAPIHandleMode(APIMode mode){ GuiAPIMode = mode; };
		static APIMode GetAPIHandleMode() { return GuiAPIMode; };

		static void SetFocus(Page* page) { focus = page; };
		static Page* GetFocus() { return focus; };

		static void SubscribeCustomUpdate(void(*updateFunc)(double)) { CustomUpdateFunc = updateFunc; };
		static void SubscribeCustomDraw(void(*drawFunc)()) { CustomDrawFunc = drawFunc; };
		static void SubscribeEnterKeyFunc(void(*enterKeyFunc)()) { EnterKeyPressedFunc = enterKeyFunc; };
		static void SubscribeEscapeKeyFunc(void(*escapeKeyFunc)()) { EscapeKeyPressedFunc = escapeKeyFunc; };

#pragma region Adds
		static void AddFont(std::string _key, TTF_Font* _font)
		{
			fonts.insert(std::pair<std::string, TTF_Font*>(_key, _font));
		};

		static void AddTexture(std::string _key, SDL_Texture* _textures)
		{
			textures.insert(std::pair<std::string, SDL_Texture*>(_key, _textures));
		};

		static void AddAudio(std::string _key, Mix_Chunk* _audio)
		{
			audio.insert(std::pair<std::string, Mix_Chunk*>(_key, _audio));
		};

		static void AddColour(std::string _key, SDL_Color _colour)
		{
			colours.insert(std::pair<std::string, SDL_Color>(_key, _colour));
		};

		static void AddRect(std::string _key, SDL_Rect _colour)
		{
			rects.insert(std::pair<std::string, SDL_Rect>(_key, _colour));
		};

		static void AddGuiContainer(std::string _key, Container* _guiContainer)
		{
			guiContainers.insert(std::pair<std::string, Container*>(_key, _guiContainer));
		};

		static void AddGuiElement(std::string _key, Element* _guiElement)
		{
			guiElements.insert(std::pair<std::string, Element*>(_key, _guiElement));
		};
#pragma endregion
#pragma region Removes
		static void RemoveFont(std::string _key)
		{
			for (std::map<std::string, TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it)
			{
				if (it->first == _key)
				{
					TTF_CloseFont(it->second);
					fonts.erase(it->first);
					break;
				}
			}
		};

		static void RemoveTexture(std::string _key)
		{
			for (std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
			{
				if (it->first == _key)
				{
					SDL_DestroyTexture(it->second);
					textures.erase(it->first);
					break;
				}
			}
		};

		static void RemoveAudio(std::string _key)
		{
			for (std::map<std::string, Mix_Chunk*>::iterator it = audio.begin(); it != audio.end(); ++it)
			{
				if (it->first == _key)
				{
					Mix_FreeChunk(it->second);
					audio.erase(it->first);
					break;
				}
			}
		};

		static void RemoveColour(std::string _key)
		{
			for (std::map<std::string, SDL_Color>::iterator it = colours.begin(); it != colours.end(); ++it)
			{
				if (it->first == _key)
				{
					colours.erase(it->first);
					break;
				}
			}
		};

		static void RemoveRect(std::string _key)
		{
			for (std::map<std::string, SDL_Rect>::iterator it = rects.begin(); it != rects.end(); ++it)
			{
				if (it->first == _key)
				{
					rects.erase(it->first);
					break;
				}
			}
		};

		static void RemoveGuiContainer(std::string _key)
		{
			for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
			{
				if (it->first == _key)
				{
					guiContainers.erase(it->first);
					break;
				}
			}
		};

		static void RemoveGuiElement(std::string _key)
		{
			for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
			{
				if (it->first == _key)
				{
					guiElements.erase(it->first);
					break;
				}
			}
		};
#pragma endregion
#pragma region Gets
		static TTF_Font* GetFont(std::string _key)
		{
			for (std::map<std::string, TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it)
			{
				if (it->first == _key)
				{
					return it->second;
				}
			}
			return nullptr;
		};

		static SDL_Texture* GetTexture(std::string _key)
		{
			for (std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
			{
				if (it->first == _key)
				{
					return it->second;
				}
			}
			return nullptr;
		};

		static Mix_Chunk* GetAudio(std::string _key)
		{
			for (std::map<std::string, Mix_Chunk*>::iterator it = audio.begin(); it != audio.end(); ++it)
			{
				if (it->first == _key)
				{
					return it->second;
				}
			}
			return nullptr;
		};

		static SDL_Color GetColor(std::string _key)
		{
			for (std::map<std::string, SDL_Color>::iterator it = colours.begin(); it != colours.end(); ++it)
			{
				if (it->first == _key)
				{
					return it->second;
				}
			}
			return{ 0, 0, 0, 0 };
		};

		static SDL_Rect GetRect(std::string _key)
		{
			for (std::map<std::string, SDL_Rect>::iterator it = rects.begin(); it != rects.end(); ++it)
			{
				if (it->first == _key)
				{
					return it->second;
				}
			}
			return{ 0, 0, 0, 0 };
		};

		static void SetAllGuiContainersInactive()
		{
			for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
			{
				it->second->Active = false;
			}
		};

		static Container* GetGuiContainer(std::string _key)
		{
			for (std::map<std::string, Container*>::iterator it = guiContainers.begin(); it != guiContainers.end(); ++it)
			{
				if (it->first == _key)
				{
					return it->second;
				}
			}
			return nullptr;
		};

		static Element* GetGuiElement(std::string _key)
		{
			for (std::map<std::string, Element*>::iterator it = guiElements.begin(); it != guiElements.end(); ++it)
			{
				if (it->first == _key)
				{
					return it->second;
				}
			}
			return nullptr;
		};
#pragma endregion

		static void BeginMainLoop();
		static void ExitMainLoop() { quit = true; };
	};
}
#endif