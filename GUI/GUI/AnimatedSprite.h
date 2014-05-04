#pragma once
#include "Sprite.h"
#include <vector>

namespace GuiAPI {
	class AnimatedSprite :
		public Sprite
	{
	public:

		AnimatedSprite(SDL_Texture *t, int posX, int posY, int sheetSzX, int sheetSzY);
		~AnimatedSprite();
		void Left();
		void Right();
		void Up();
		void Down();
		void Update(double time);
		virtual void Draw();
	private:

		int width;
		int height;
		int lastUpdated;
		int timeElapsed;
		int currentFrame;
		int sheetX;
		int sheetY;
		int row;
		std::vector<SDL_Rect>clips;

		enum Direction { DOWN, LEFT, UP, RIGHT };

		SDL_Texture *sheet;

		int x;
		int y;
	};
}

