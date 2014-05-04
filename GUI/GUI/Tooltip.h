#pragma once
#include "Label.h"

namespace GuiAPI {
	class Tooltip : public Label
	{
	private:
		SDL_Texture *bgTexture;

	public:
		Tooltip(SDL_Texture *_tex, const std::string &_text, SDL_Rect _rect, TTF_Font *_font, SDL_Color _color);
		virtual ~Tooltip();

		virtual void Update(double _time);
		virtual void Draw();

		virtual void OnMouseHover(SDL_MouseMotionEvent e);
		virtual void OnMouseMotion(SDL_MouseMotionEvent e);
	};
}