#pragma once
#ifndef GUI_CONTAINER_H
#define GUI_CONTAINER_H

#include "GuiObject.h"

#include "SDLIncludes.h"
#include "APIEvents.h"

//-- Include all GuiObjects so that Container can return specified types
#include "Element.h"
#include "Button.h"
#include "Label.h"
#include "TextField.h"
#include "Checkbox.h"
#include "Slider.h"
#include "GridLayer.h"

namespace GuiAPI {
	class Container : public GuiObject
	{
	private:
		std::unordered_map<std::string, Container*> guiContainers;
		std::unordered_map<std::string, Element*> guiElements;

		Mix_Chunk* music;
		Mix_Chunk* sfx1;
		Mix_Chunk* sfx2;

		SDL_Rect position;

		void(*onEscapeKeyPressed)();
		void(*onEnterKeyPressed)();

		void CleanMemory()
		{
			guiContainers.clear();
			guiElements.clear();
		}

	public:

		Container();
		~Container() { CleanMemory(); GuiObject::~GuiObject(); }

		void SetBackgroundAudio(Mix_Chunk* _music) { music = _music; }
		void MusicPlay() { if (music != nullptr) Mix_PlayChannel(AudioChannel::MusicChannel, music, -1); }
		void MusicPause(){ Mix_Pause(AudioChannel::MusicChannel); }

		void SetSfx1Audio(Mix_Chunk* _sfx1) { sfx1 = _sfx1; }
		void Sfx1Play() { if (sfx1 != nullptr) Mix_PlayChannel(AudioChannel::SoundEffectChannel1, sfx1, 0); }
		void Sfx1Pause(){ Mix_Pause(AudioChannel::SoundEffectChannel1); }

		void SetSfx2Audio(Mix_Chunk* _sfx2) { sfx2 = _sfx2; }
		void Sfx2Play() { if (sfx2 != nullptr) Mix_PlayChannel(AudioChannel::SoundEffectChannel2, sfx2, 0); }
		void Sfx2Pause(){ Mix_Pause(AudioChannel::SoundEffectChannel2); }

#pragma region Adds
		void AddGuiContainer(std::string _key, Container* _guiContainer)
		{
			_guiContainer->SetPosition(position);

			guiContainers.emplace(_key, _guiContainer);
		}

		void AddGuiElement(std::string _key, Element* _guiElement)
		{
			_guiElement->SetOffset(position);

			guiElements.emplace(_key, _guiElement);
		}

#pragma endregion
#pragma region Removes
		void RemoveGuiContainer(std::string _key)
		{
			guiContainers.erase(_key);
		}

		void RemoveGuiElement(std::string _key)
		{
			guiElements.erase(_key);
		}
#pragma endregion
#pragma region Gets
		Container* GetGuiContainer(std::string _key)
		{
			return guiContainers.at(_key);
		}

		Element* GetGuiElement(std::string _key)
		{
			return guiElements.at(_key);
		}

		GridLayer* GetGridLayer(std::string _key)
		{
			return (GridLayer*)guiElements.at(_key);
		}

		Button* GetButton(std::string _key)
		{
			return (Button*)guiElements.at(_key);
		}

		TextField* GetTextField(std::string _key)
		{
			return (TextField*)guiElements.at(_key);
		}

		Label* GetLabel(std::string _key)
		{
			return (Label*)guiElements.at(_key);
		}

		Checkbox* GetCheckbox(std::string _key)
		{
			return (Checkbox*)guiElements.at(_key);
		}

		Slider* GetSlider(std::string _key)
		{
			return (Slider*)guiElements.at(_key);
		}
#pragma endregion

		void CheckEvents(SDL_Event e);
		void Update(double time);
		void Draw();

		SDL_Rect GetPosition() { return position; }
		void SetPosition(SDL_Rect _position);

		void SubscribeOnEscapeKeyPressed(void(*func)()) { onEscapeKeyPressed = func; }
		void SubscribeOnEnterKeyPressed(void(*func)()) { onEnterKeyPressed = func; }

		void OnMouseClick();
		void OnMouseMotion(SDL_MouseMotionEvent e);
		void OnMouseDown(SDL_MouseButtonEvent e);
		void OnMouseUp(SDL_MouseButtonEvent e);

		void OnEnterKeyPressed();
		void OnEscapeKeyPressed();
		void OnKeyboardDown(SDL_KeyboardEvent e);
		void OnKeyboardUp(SDL_KeyboardEvent e);
		void OnTextInput(SDL_TextInputEvent e);
	};
}
#endif