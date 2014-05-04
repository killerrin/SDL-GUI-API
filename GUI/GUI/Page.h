#pragma once
#ifndef PAGE_H
#define PAGE_H

#include "Container.h"
//#include "ScreenFader.h"
namespace GuiAPI {
	class Page
	{
	protected:
		Container* content;

	public:
		Page() { content = new Container(); };
		virtual ~Page() { delete content; };

		//===================
		//-- Must Impliment
		//===================
		virtual void Load() {};
		virtual void Update(double time) { content->Update(time); };
		virtual void Draw() { content->Draw(); };

		//===================
		//-- Helper Methods
		//===================
		Container* GetContent() { return content; };

		//===========
		//-- Events
		//===========
		void OnMouseClick(){ content->OnMouseClick(); };
		void OnMouseMotion(SDL_MouseMotionEvent e){ content->OnMouseMotion(e); };
		void OnMouseDown(SDL_MouseButtonEvent e){ content->OnMouseDown(e); };
		void OnMouseUp(SDL_MouseButtonEvent e){ content->OnMouseUp(e); };

		void OnEnterKeyPressed(){ content->OnEnterKeyPressed(); };
		void OnEscapeKeyPressed(){ content->OnEscapeKeyPressed(); };
		void OnKeyboardDown(SDL_KeyboardEvent e){ content->OnKeyboardDown(e); };
		void OnKeyboardUp(SDL_KeyboardEvent e){ content->OnKeyboardUp(e); };
		void OnTextInput(SDL_TextInputEvent e){ content->OnTextInput(e); };
	};
}
#endif