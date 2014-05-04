#include "Checkbox.h"
using namespace GuiAPI;

Checkbox::Checkbox(SDL_Rect _rect, SDL_Color _checkColour, SDL_Color _outlineColour)
:Element(GUIHelper::SolidColourTexture(_rect.w - (4 * 2) - 2, _rect.h - (4 * 2) - 2, _checkColour), _rect)
{
	outlineTopBottom = GUIHelper::SolidColourTexture(_rect.w, 4, _outlineColour);
	outlineLeftRight = GUIHelper::SolidColourTexture(4, _rect.h, _outlineColour);
}


Checkbox::~Checkbox()
{
	SDL_DestroyTexture(outlineTopBottom);
	SDL_DestroyTexture(outlineLeftRight);

	Element::~Element();
}

void Checkbox::Update(double _time)
{
	if (Active) {
		if (Enabled) {
			Element::Update(_time);
		}
	}
}

void Checkbox::Draw()
{
	if (Active){
		SDL_RenderCopyEx(Window::Renderer(), outlineTopBottom, NULL, &GUIHelper::RectHelper(rect.x - BorderCheckSeperation, rect.y - BorderCheckSeperation, rect.w + BorderCheckSeperation + 2, BorderWidth), 0, NULL, flip);
		SDL_RenderCopyEx(Window::Renderer(), outlineTopBottom, NULL, &GUIHelper::RectHelper(rect.x - BorderCheckSeperation, rect.y + rect.h + 2, rect.w + BorderCheckSeperation + BorderWidth + 2, BorderWidth), 0, NULL, flip);

		SDL_RenderCopyEx(Window::Renderer(), outlineLeftRight, NULL, &GUIHelper::RectHelper(rect.x - BorderCheckSeperation, rect.y - BorderCheckSeperation, BorderWidth, rect.h + BorderCheckSeperation + 2), 0, NULL, flip);
		SDL_RenderCopyEx(Window::Renderer(), outlineLeftRight, NULL, &GUIHelper::RectHelper(rect.x + rect.w + 2, rect.y - BorderCheckSeperation, BorderWidth, rect.h + BorderCheckSeperation + BorderWidth), 0, NULL, flip);
		
		if (Checked)
			Element::Draw();
	}
}

void Checkbox::OnMouseClick()
{
	Checked = !Checked;

	Element::OnMouseClick();
}
