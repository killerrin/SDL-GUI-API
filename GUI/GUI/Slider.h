#pragma once
#include "Element.h"
namespace GuiAPI {
	class Slider :
		public Element
	{
	private:
		SDL_Texture* slider;
		SDL_Rect sliderRect;

		bool isPressedDown;

		void ClampSlider();

	public:

		Slider(SDL_Rect _rect, SDL_Texture* _sliderBar, SDL_Texture* _slider);
		virtual ~Slider();

		virtual void Update(double _time);
		virtual void Draw();

		int Value()
		{
			int value = sliderRect.x - rect.x;
			return value;
		}

		virtual void OnMouseDown(SDL_MouseButtonEvent e);
		virtual void OnMouseUp(SDL_MouseButtonEvent e);
		virtual void OnMouseClick();
		virtual void OnMouseMotion(SDL_MouseMotionEvent e);

	};
}
