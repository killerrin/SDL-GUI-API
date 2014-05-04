#pragma once
#ifndef SCREEN_FADER_H
#define SCREEN_FADER_H

#include <SDL.h>
#include <math.h>
#include "GUI.h"
#include <stdio.h>

namespace GuiAPI {
	class ScreenFader
	{
	protected:
		ScreenFader();
		static ScreenFader* instance;

	public:
		static ScreenFader* GetInstance();
		~ScreenFader();

		void Load();
		void Update(double _time);
		void FadeIn();
		void FadeOut();
		void FadeToNewScreen(std::string _currentScr, std::string _newScr);
		void Draw();
		void SetColor(SDL_Color _color);
	private:
		SDL_Texture *fader;
		SDL_Color color;
		bool isFadingIn, isFadingOut;
		int alpha;
	};
}
#endif