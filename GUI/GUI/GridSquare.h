#pragma once
#include "Element.h"

namespace GuiAPI {
	class GridSquare : public Element
	{
	public:
		SDL_Rect m_sourceRectangle = SDL_Rect();
		SDL_Rect m_destinationRectangle = SDL_Rect();
		SDL_Texture* m_gridTexture;

		GridSquare();
		//GridSquare(SDL_Texture* _tileSet, GridSquare _gridSquare, unsigned int width, unsigned int height);
		//GridSquare(GridSquare _gridSquare, unsigned int width, unsigned int height);
		~GridSquare(void);

		virtual void Draw();

		virtual void HandleMouseClickEvent();
		virtual void HandleMouseMotionEvent(SDL_MouseMotionEvent e);
		virtual void HandleMouseHoverEvent(SDL_MouseMotionEvent e);
		virtual void HandleMouseDownEvent(SDL_MouseButtonEvent e);
		virtual void HandleMouseUpEvent(SDL_MouseButtonEvent e);
	};
}