#include "Tooltip.h"
using namespace GuiAPI;

Tooltip::Tooltip(SDL_Texture *_tex, const std::string &_text, SDL_Rect _rect, TTF_Font *_font, SDL_Color _color) : 
Label(_text, _rect, _font, _color)
{
	bgTexture = _tex;
	printf("tooltip initialized\n");
}

Tooltip::~Tooltip()
{
	delete &bgTexture;

	Label::~Label();
}

void Tooltip::Update(double _time)
{
	if (Active)
	{
		if (Enabled)
			Label::Update(_time);
	}
}

void Tooltip::Draw()
{
	if (Active)
	{
		SDL_RenderCopyEx(Window::Renderer(), bgTexture, NULL, &rect, 0., NULL, flip);
		Label::Draw();
	}
}

void Tooltip::OnMouseHover(SDL_MouseMotionEvent e)
{
	Active = true;
}

void Tooltip::OnMouseMotion(SDL_MouseMotionEvent e)
{
	Active = false;
}