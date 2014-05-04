#pragma once
#include "GridSquare.h"

namespace GuiAPI {
	class GridLayer : public Element {
	public:
		char tileSize;
		unsigned int rows;
		unsigned int columns;

		bool Active;
		bool Enabled;
		std::vector<GridSquare*> layer;

		GridLayer();
		//GridLayer(GridLayer _gridLayer, GridSquare _gridSquares[]);
		//GridLayer(SDL_Texture* _tileTexture, GridLayer _gridLayer, GridSquare _gridSquares[]);
		~GridLayer(void);

		virtual void Update(double time);
		virtual void Draw();

		void HandleMouseClickEvent();
		void HandleMouseMotionEvent(SDL_MouseMotionEvent e);
		void HandleMouseDownEvent(SDL_MouseButtonEvent e);
		void HandleMouseUpEvent(SDL_MouseButtonEvent e);

		void SetPosition(SDL_Rect){

		}
	};
}
