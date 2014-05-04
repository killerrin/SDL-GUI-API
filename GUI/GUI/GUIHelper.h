#pragma once
#ifndef API_HELPER_H
#define API_HELPER_H

#include "SDLIncludes.h"
#include "APIEvents.h"
#include "Window.h"

namespace GuiAPI {
	class GUIHelper
	{
	public:

		static SDL_Texture* SolidColourTexture(int width, int height, SDL_Color colour)
		{
			SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 1); // 16
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, colour.r, colour.g, colour.b));

			SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::Renderer(), surface);
			SDL_SetTextureAlphaMod(texture, colour.a);
			return texture;
		}

		static SDL_Texture* LoadBMPImage(const std::string &file) { return Window::LoadImage(file); }
		static SDL_Texture* LoadPNGTexture(const std::string &file) { return Window::LoadTexture(file); }
		static TTF_Font* LoadFont(const std::string &file, int fontSize) { return Window::LoadFont(file, fontSize); }

		static Mix_Chunk* LoadAudioFile(const std::string &file) {
			Mix_Chunk *sound = NULL;

			sound = Mix_LoadWAV(file.c_str());
			//sound = Mix_LoadWAV("Resources/Audios/test.wav");
			if (sound == NULL) {
				std::cout << Mix_GetError() << std::endl;
			}
			return sound;
		}

		static SDL_Rect RectHelper(int x, int y, int w, int h) { return{ x, y, w, h }; } // Window::RectHelper(x, y, w, h); }
		static SDL_Color ColourHelper(int r, int g, int b, int a) { return{ r, g, b, a }; }
		static bool Intersects(SDL_Rect _rect1, SDL_Rect _rect2)
		{
			if (SDL_HasIntersection(&_rect1, &_rect2) == SDL_TRUE)
			{
				return true;
			}
			else if (SDL_HasIntersection(&_rect1, &_rect2) == SDL_FALSE)
			{
				return false;
			}
			return false;
		}

		static bool DidKeyGetPressed(SDL_Scancode key) { return APIEvents::DidKeyGetPressed(key); }
		static bool DidMouseClick() { return APIEvents::DidMouseClick(); }

		static bool ToggleTextInput()
		{
			if (APIEvents::SDLTextInputEnabled) { SDL_StopTextInput(); }
			else { SDL_StartTextInput(); }

			APIEvents::SDLTextInputEnabled = !APIEvents::SDLTextInputEnabled;
			return APIEvents::SDLTextInputEnabled;
		}

		static void ToggleAllAudio() { Window::ToggleAllAudio(); }

		static int GetMusicVolume(int _level) { return Window::GetMusicVolume(); }
		static int GetSoundEffect1Volume(int _level) { return Window::GetSoundEffect1Volume(); }
		static int GetSoundEffect2Volume(int _level) { return Window::GetSoundEffect2Volume(); }

		static void SetMusicVolume(int _level) { Window::SetMusicVolume(_level); }
		static void SetSoundEffect1Volume(int _level) { Window::SetSoundEffect1Volume(_level); }
		static void SetSoundEffect2Volume(int _level) { Window::SetSoundEffect2Volume(_level); }
	};
}
#endif