#include "Sprite.h"
using namespace GuiAPI;

Sprite::Sprite(SDL_Texture *tex, int posX,int posY)
	:Element(tex, { 0, 0, 0, 0 })
{
	SDL_QueryTexture(tex, NULL, NULL, &rectWidth, &rectHeight);
	Element::SetPosition(posX, posY);
	Element::SetWidthHeight(rectWidth, rectHeight);
}

Sprite::~Sprite()
{
}

void Sprite::Update(double time)
{
	Element::Update(time);
}

void Sprite::Draw()
{
	Element::Draw();
}
