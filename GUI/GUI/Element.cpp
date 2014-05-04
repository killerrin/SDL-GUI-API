#include "Element.h"
using namespace GuiAPI;

Element::Element() :GuiObject()
{
	texture = nullptr;
	rect = { 0, 0, 0, 0 };
	SetupHelper();
}
Element::Element(SDL_Texture *_texture, SDL_Rect _rect) :GuiObject()
{
	texture = _texture;
	rect = _rect;
	SetupHelper();
}

void Element::SetupHelper()
{
	onMouseClickFunc = nullptr;
	onMouseMotionFunc = nullptr;
	onMouseHoverFunc = nullptr;
	onMouseDownFunc = nullptr;
	onMouseUpFunc = nullptr;

	onEscapeKeyPressed = nullptr;
	onEnterKeyPressed = nullptr;
	onKeyboardDownFunc = nullptr;
	onKeyboardUpFunc = nullptr;
	onTextInputFunc = nullptr;

	offset = { 0, 0, 0, 0 };
	padding = { 0, 0, 0, 0 };
}

Element::~Element() {
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		rect.w = rect.h = 0;
	}
	delete &flip;

	GuiObject::~GuiObject();
}


void Element::Update(double _time) { if (Active) { if (Enabled) { GuiObject::Update(_time); } } }
void Element::Draw()
{
	if (Active) {
		SDL_Rect rectangle = rect;
		rectangle.x += offset.x + padding.x;
		rectangle.y += offset.y + padding.y;

		SDL_RenderCopyEx(Window::Renderer(), texture, NULL, &rectangle, 0, NULL, flip); //SDL_RenderCopyEx(Window::Renderer(), texture, NULL, &rect, 0, NULL, flip);

		GuiObject::Draw();
	}
}

bool Element::Intersects(SDL_Rect _rect)
{
	SDL_Rect truePosition = rect;
	truePosition.x += offset.x + padding.x;
	truePosition.y += offset.y + padding.y;

	if (SDL_HasIntersection(&truePosition, &_rect) == SDL_TRUE)
	{
		return true;
	}
	else if (SDL_HasIntersection(&truePosition, &_rect) == SDL_FALSE)
	{
		return false;
	}

	return false;
}

void Element::OnMouseClick() {
	if (Enabled && Active) {
		if (onMouseClickFunc != NULL) {
			(*onMouseClickFunc)();
		}
	}
}
void Element::OnMouseMotion(SDL_MouseMotionEvent e) {
	if (Enabled && Active) {
		if (onMouseMotionFunc != NULL) {
			(*onMouseMotionFunc)(e);
		}
	}
}
void Element::OnMouseHover(SDL_MouseMotionEvent e) {
	if (Enabled && Active) {
		if (onMouseHoverFunc != NULL) {
			(*onMouseHoverFunc)(e);
		}
	}
}
void Element::OnMouseDown(SDL_MouseButtonEvent e) {
	if (Enabled && Active) {
		if (onMouseDownFunc != NULL) {
			(*onMouseDownFunc)(e);
		}
	}
}
void Element::OnMouseUp(SDL_MouseButtonEvent e) {
	if (Enabled && Active) {
		if (onMouseUpFunc != NULL) {
			(*onMouseUpFunc)(e);
		}
	}
}

void Element::OnEscapeKeyPressed() {
	if (Enabled && Active) {
		if (onEscapeKeyPressed != NULL) {
			(*onEscapeKeyPressed)();
		}
	}
}
void Element::OnEnterKeyPressed() {
	if (Enabled && Active) {
		if (onEnterKeyPressed != NULL) {
			(*onEnterKeyPressed)();
		}
	}
}
void Element::OnKeyboardDown(SDL_KeyboardEvent e) {
	if (Enabled && Active) {
		if (onKeyboardDownFunc != NULL) {
			(*onKeyboardDownFunc)(e);
		}
	}
}
void Element::OnKeyboardUp(SDL_KeyboardEvent e) {
	if (Enabled && Active) {
		if (onKeyboardUpFunc != NULL) {
			(*onKeyboardUpFunc)(e);
		}
	}
}
void Element::OnTextInput(SDL_TextInputEvent e) {
	if (Enabled && Active) {
		if (onTextInputFunc != NULL) {
			(*onTextInputFunc)(e);
		}
	}
}