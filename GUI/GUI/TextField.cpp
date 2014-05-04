#include "TextField.h"
using namespace GuiAPI;

TextField::TextField(SDL_Rect _rect, TTF_Font* _font, SDL_Color _textColour)
:Label("", _rect, _font, _textColour)
{
	backgroundTexture = GUIHelper::SolidColourTexture(_rect.w, _rect.h, { 255, 255, 255, 155 });

	CharacterLimit = -1;

	textRect = _rect;
	RenderText();
}

TextField::~TextField()
{
	SDL_DestroyTexture(backgroundTexture);

	Element::~Element();
}

void TextField::Update(double _time)
{
	if (Active) {
		if (Enabled) {
			Element::Update(_time);
		}
	}
}

void TextField::Draw()
{
	if (Active) {
		SDL_Rect rectangle = rect;
		rectangle.x += offset.x + padding.x - 2;
		rectangle.y += offset.y + padding.y;
		rectangle.w = textRect.w;
		SDL_RenderCopyEx(Window::Renderer(), backgroundTexture, NULL, &rectangle, 0., NULL, flip);

		Label::Draw();
	}
}

void TextField::Clear()
{
	Label::Clear();
	RenderText();
}
void TextField::AddToString(char _added)
{
	if (CharacterLimit == -1 || GetStringSize() < CharacterLimit) {
		printf("Character Pressed: %c\n", _added);

		text.push_back(_added);
		//text += _added;

		RenderText();
	}
}

void TextField::RemoveLastCharacterFromString()
{
	if (GetStringSize() == 0)
		return;
	
	text.pop_back();
	//text.erase(text.length() - 1);
	
	RenderText();
}

std::string TextField::GetText()
{
	return text;
}

int TextField::GetStringSize()
{
	return text.length();
}

void TextField::RenderText() { RenderText(text); }
void TextField::RenderText(std::string &_text)
{
	SDL_DestroyTexture(texture);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, _text.c_str(), fontColor);

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

void TextField::OnEnterKeyPressed()
{
	if (Active && Enabled)
	{
		Label::OnEnterKeyPressed();
	}
}
void TextField::OnKeyboardDown(SDL_KeyboardEvent e)
{
	if (Active && Enabled)
	{
		std::cout << "KeyPressed" << std::endl;

		//Handle backspace
		if (e.keysym.sym == SDLK_BACKSPACE)
		{
			//lop off character
			RemoveLastCharacterFromString();

			std::cout << "Backspace Pressed" << std::endl;
		}

		Label::OnKeyboardDown(e);
	}
}
void TextField::OnKeyboardUp(SDL_KeyboardEvent e)
{
	if (Active && Enabled)
	{
		Label::OnKeyboardUp(e);
	}
}
void TextField::OnTextInput(SDL_TextInputEvent e)
{
	if (Active && Enabled)
	{
		std::cout << "Text Input" << std::endl;

		//Not pasting
		if (!((e.text[0] == 'v' || e.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
		{
			//Append character
			AddToString(*e.text); // inputText += e.text.text;
								  // renderText = true;
		}

		Label::OnTextInput(e);
	}
}