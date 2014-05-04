#pragma once
#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include "GuiObject.h"

#include "Window.h"
#include "GUIHelper.h"

namespace GuiAPI {
	class Element : public GuiObject
	{
	protected:
		GuiObject* parent;

		SDL_Texture *texture;
		SDL_Rect rect;
		SDL_Rect offset;
		SDL_Rect padding;
		SDL_RendererFlip flip = SDL_FLIP_NONE;

		void(*onMouseClickFunc)();
		void(*onMouseMotionFunc)(SDL_MouseMotionEvent e);
		void(*onMouseHoverFunc)(SDL_MouseMotionEvent e);
		void(*onMouseDownFunc)(SDL_MouseButtonEvent e);
		void(*onMouseUpFunc)(SDL_MouseButtonEvent e);

		void(*onEscapeKeyPressed)();
		void(*onEnterKeyPressed)();
		void(*onKeyboardDownFunc)(SDL_KeyboardEvent e);
		void(*onKeyboardUpFunc)(SDL_KeyboardEvent e);
		void(*onTextInputFunc)(SDL_TextInputEvent e);

		void SetupHelper();
	public:
		Element();
		Element(SDL_Texture *_texture, SDL_Rect _rect);
		~Element();

		virtual void Update(double _time);
		virtual void Draw();

		bool Intersects(SDL_Rect _rect);

		float Layer = 0.0f;
		int GetHeight() { return rect.h; }
		int GetWidth() { return rect.w; }
		int GetX() { return rect.x; }
		int GetY() { return rect.y; }
		SDL_Rect GetPosition() { return rect; }
		SDL_Rect GetOffset() { return offset; }
		SDL_Rect GetPadding() { return padding; }

		void SetPosition(int _x, int _y) { rect.x = _x; rect.y = _y; }
		void SetWidthHeight(int _w, int _h)	{ rect.w = _w; rect.h = _h; }
		void SetScale(int _xScale, int _yScale)	{ rect.w *= _xScale; rect.h *= _yScale; }
		virtual void SetOffset(SDL_Rect _rect){ offset = _rect; }
		virtual void SetPadding(SDL_Rect _rect) { padding = _rect; }

		void SubscribeOnMouseClick(void(*func)()) { onMouseClickFunc = func; }
		void SubscribeOnMouseMove(void(*func)(SDL_MouseMotionEvent e)) { onMouseMotionFunc = func; }
		void SubscribeOnMouseHover(void(*func)(SDL_MouseMotionEvent e)) { onMouseHoverFunc = func; }
		void SubscribeOnMouseDown(void(*func)(SDL_MouseButtonEvent e)) { onMouseDownFunc = func; }
		void SubscribeOnMouseUp(void(*func)(SDL_MouseButtonEvent e)) { onMouseUpFunc = func; }

		void SubscribeOnEscapeKeyPressed(void(*func)()) { onEscapeKeyPressed = func; }
		void SubscribeOnEnterKeyPressed(void(*func)()) { onEnterKeyPressed = func; }
		void SubscribeOnKeyboardDown(void(*func)(SDL_KeyboardEvent e)) { onKeyboardDownFunc = func; }
		void SubscribeOnKeyboardUp(void(*func)(SDL_KeyboardEvent e)) { onKeyboardUpFunc = func; }
		void SubscribeOnTextInput(void(*func)(SDL_TextInputEvent e)) { onTextInputFunc = func; }

		virtual void OnMouseClick();
		virtual void OnMouseMotion(SDL_MouseMotionEvent e);
		virtual void OnMouseHover(SDL_MouseMotionEvent e);
		virtual void OnMouseDown(SDL_MouseButtonEvent e);
		virtual void OnMouseUp(SDL_MouseButtonEvent e);

		virtual void OnEscapeKeyPressed();
		virtual void OnEnterKeyPressed();
		virtual void OnKeyboardDown(SDL_KeyboardEvent e);
		virtual void OnKeyboardUp(SDL_KeyboardEvent e);
		virtual void OnTextInput(SDL_TextInputEvent e);
	};
}
#endif


