#include "AnimatedSprite.h"
using namespace GuiAPI;

AnimatedSprite::AnimatedSprite(SDL_Texture *tex, int posX, int posY, int sheetSzX, int sheetSzY)
:Sprite(tex, posX, posY)
{
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);

	sheet = tex;
	x = posX;
	y = posY;
	sheetX = sheetSzX;
	sheetY = sheetSzY;
	
	//clips.reserve(sheetX*sheetY);
	clips.resize(sheetX * sheetY);
	//only animating minions
	width /= sheetX; //width of each frame
	height /= sheetY;
	for (int j = 0; j < sheetY; j++)
	{
		for (int i = 0; i < sheetX; i++)
		{
			//clips.push_back(SDL_Rect{ 0, 0, 0, 0 });
			clips[i + j * sheetX].x = i*width;
			clips[i + j * sheetX].y = j*height;
			clips[i + j * sheetX].w = width;
			clips[i + j * sheetX].h = height;
		}
	}
	currentFrame = 0;
	lastUpdated = SDL_GetTicks();
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Left()
{
	
	row = LEFT;
	currentFrame = row * sheetY;
}
void AnimatedSprite::Right()
{
	row = RIGHT;
	currentFrame = row * sheetY;
}
void AnimatedSprite::Up()
{
	row = UP;
	currentFrame = row * sheetY;
}
void AnimatedSprite::Down()
{
	row = DOWN;
	currentFrame = row * sheetY;
}
void AnimatedSprite::Update(double time)
{
	timeElapsed = SDL_GetTicks();
	if (timeElapsed - lastUpdated >= 83)//about 12 frames/second 1000ms/12frames=83.3
	{
		if (row == LEFT)
		{
			if (currentFrame == (row * sheetY) + sheetY - 1)//when left animation reaches last frame, set animation back to first frame
				currentFrame = row * sheetY;
		}
		else if (row == RIGHT)
		{
			if (currentFrame == (row * sheetY) + sheetY - 1)
				currentFrame = row * sheetY;
		}
		else if (row == UP)
		{
			if (currentFrame == (row * sheetY) + sheetY - 1)
				currentFrame = row * sheetY;
		}
		else if (row == DOWN)
		{
			if (currentFrame == (row * sheetY) + sheetY - 1)
				currentFrame = row * sheetY;
		}
		
		currentFrame++;
		lastUpdated = timeElapsed;
	}

	Sprite::Update(time);
}
void AnimatedSprite::Draw()
{
	SDL_RenderCopy(Window::Renderer(), sheet, &clips[currentFrame], &rect);
}