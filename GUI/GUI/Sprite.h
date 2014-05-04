#pragma once
#include "GUI.h"

namespace GuiAPI {
	class Sprite : public Element
	{
	private:
		int rectWidth;
		int rectHeight;
	public:
		Sprite(SDL_Texture *t, int posX, int posY);
		~Sprite();
		virtual void Update(double time);
		virtual void Draw();
	};
}

