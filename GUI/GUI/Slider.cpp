#include "Slider.h"
using namespace GuiAPI;

Slider::Slider(SDL_Rect _rect, SDL_Texture* _sliderBar, SDL_Texture* _slider)
:Element(_sliderBar, _rect)
{
	slider = _slider;
	sliderRect = { (_rect.x + _rect.w) - 10 ,
					_rect.y - (_rect.h / 2),
					10,
					_rect.h + 20 };
	
	isPressedDown = false;
}


Slider::~Slider()
{
	SDL_DestroyTexture(slider);

	Element::~Element();
}

void Slider::Update(double _time)
{
	if (Active) {
		if (Enabled) {
			Element::Update(_time);
		}
	}
}

void Slider::Draw()
{
	if (Active){
		Element::Draw();

		SDL_RenderCopyEx(Window::Renderer(), slider, NULL, &sliderRect, 0, NULL, flip);
	}
}

void Slider::ClampSlider()
{
	sliderRect.x = APIEvents::MousePosition.x;

	if (sliderRect.x < rect.x) sliderRect.x = rect.x;
	else if (sliderRect.x >(rect.x + rect.w)) sliderRect.x = rect.x + rect.w - sliderRect.w;
}

void Slider::OnMouseDown(SDL_MouseButtonEvent e)
{
	isPressedDown = true;
	std::cout << "Pressed Down" << std::endl;
	Element::OnMouseDown(e);
}
void Slider::OnMouseUp(SDL_MouseButtonEvent e)
{
	std::cout << "Up" << std::endl;
	isPressedDown = false;
	Element::OnMouseUp(e);
}
void Slider::OnMouseClick()
{
	ClampSlider();
}

void Slider::OnMouseMotion(SDL_MouseMotionEvent e)
{
	if (isPressedDown){
		ClampSlider();
	}
}
