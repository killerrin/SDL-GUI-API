#include "Label.h"
using namespace GuiAPI;

Label::Label(const std::string &_text, SDL_Rect _rect, TTF_Font* _font, SDL_Color _color)
:Element(nullptr, _rect)
{
	text = _text;
	font = _font;
	fontColor = _color;

	RenderText();
}


Label::~Label()
{
	delete &text;
	delete &fontColor;

	Element::~Element();
}

void Label::RenderText() { RenderText(text); }
void Label::RenderText(std::string &_text)
{
	if (_text.length() == 0) _text = " ";

	SDL_DestroyTexture(texture);

	SDL_Surface *textSurface = TTF_RenderText_Blended_Wrapped(font, _text.c_str(), fontColor, rect.w);
	if (textSurface != NULL)
	{
		texture = SDL_CreateTextureFromSurface(Window::Renderer(), textSurface);

		if (texture == NULL)
		{
			printf("Unable to create texture from textSurface. SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			text = _text;
			rect.h = textSurface->h;
			rect.w = textSurface->w;
		}

		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
	}
}

void Label::Update(double _time)
{
	if (Active) {
		if (Enabled) {
			Element::Update(_time);
		}
	}
}

void Label::Draw()
{
	if (Active){
		Element::Draw();
	}
}

void Label::Clear()
{
	text = "";
	RenderText();
}