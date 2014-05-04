#pragma once
#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Label.h"

namespace GuiAPI {
	class TextField :
		public Label
	{
	private:
		SDL_Texture* backgroundTexture;
		SDL_Rect textRect;
	public:
		TextField(SDL_Rect _rect, TTF_Font* _font, SDL_Color _textColour);
		virtual ~TextField();

		int CharacterLimit = -1;

		virtual void Clear();
		void AddToString(char _added);
		void RemoveLastCharacterFromString();
		int GetStringSize();
		std::string GetText();

		virtual void RenderText();
		virtual void RenderText(std::string &_text);

		virtual void Update(double _time);
		virtual void Draw();

		virtual void OnEnterKeyPressed();
		virtual void OnKeyboardDown(SDL_KeyboardEvent e);
		virtual void OnKeyboardUp(SDL_KeyboardEvent e);
		virtual void OnTextInput(SDL_TextInputEvent e);
	};
}
#endif