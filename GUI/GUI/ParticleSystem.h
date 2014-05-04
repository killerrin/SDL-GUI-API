#pragma once
#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Element.h"
#include <math.h>

namespace GuiAPI {
	/* PARTICLE CLASS - DO NOT ALTER */
	class Particle : public Element{
	public:
		Particle(){}
		Particle(SDL_Texture* _texture)
		{
			alive = true;
			alpha = 255;
			texture = _texture;
			//speed = (rand() % 20) + 5; //Default the speed to be random. Override later if you desire another outcome
			SDL_QueryTexture(texture, NULL, NULL, &rectWidth, &rectHeight); //Grab the texture data and set the width and height of our dst rectangle to the textures dimensions
			rect = { 0, 0, rectWidth, rectHeight };
			SetDirection(0, 0);
			originalX = (float)GetPosition().x;
			originalY = (float)GetPosition().y;

		}
		virtual void Update(double time)
		{
			if (Active)
			{
				//Offsets and padding prior to updating 
				if (alive)
				{

					rect.x += offset.x + padding.x;
					rect.y += offset.y + padding.y;
					SetPosition((float)(GetPosition().x + (directionX * speed)), //Set the position of the particle and update based on its directional vector and speed
						(float)(GetPosition().y + (directionY * speed)));

					//Reduce the alpha over time
					if (alpha >= 10){
						alpha -= (int)(time / (2 * timeInSeconds));
					}
					else{
						alpha = 0;
					}
					if (alpha == 0){ alive = false; } //If the alpha is equal to zero, the particle is no longer living

					SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //Change blending mode of the texture
					SDL_SetTextureAlphaMod(texture, alpha); //Set the alpha of the texture
				}

			}
		}
		virtual void Draw()
		{
			if (Active)
			{
				if (alive)
				{
					rect.x += offset.x + padding.x;
					rect.y += offset.y + padding.y;
					SDL_RenderCopyEx(Window::Renderer(), texture, NULL, &rect, 0, NULL, flip);
				}
			}
		}

		float GetDirectionX() { return directionX; }
		float GetDirectionY() { return directionY; }

		void SetPosition(float x, float y) { rect.x = (int)x; rect.y = (int)y; }
		void SetOriginalPosition(float x, float y){ originalX = x, originalY = y; }
		void SetDirection(float x, float y){ directionX = x; directionY = y; }
		void SetSpeed(float _speed) { speed = _speed; }
		void SetAlphaTimer(float _time) { timeInSeconds = _time; }
		void ResetParticle() { alpha = 255; alive = true, SetPosition(originalX, originalY); }
		bool isAlive() { return alive; }

	private:
		int rectWidth, rectHeight, alpha;
		float directionX, directionY, speed, originalX, originalY, timeInSeconds;
		bool alive;
	};



	/* BASE PARTICLESYSTEM CLASS */
	class ParticleSystem : public Element{
	public:
		ParticleSystem();
		~ParticleSystem();
		virtual void Setup();

		//Setters
		void SetPosition(float x, float y);
		void SetSpeed(float _speed);
		void SetTexture(SDL_Texture* _texture) { m_ParticleTextures.push_back(_texture); }
		void SetTextures(std::vector<SDL_Texture*> _textures) {
			for (int i = 0; i < _textures.size(); i++)
				m_ParticleTextures.push_back(_textures.at(i));
		}
		void SetRepeat(bool _repeat) { repeating = _repeat; }
		void SetRandom(bool myBool) { randomSpeeds = myBool; }

		//Getters
		float GetSpeed(){ return particleSpeed; }
		bool isRepeating(){ return repeating; }
		bool isRandomSpeeds(){ return randomSpeeds; }

		void Initialize(size_t numberOfParticles);
		std::vector<Particle*> particleList;

	private:
		bool randomSpeeds;
		bool repeating;
		float particleSpeed;
		std::vector<SDL_Texture*> m_ParticleTextures;
		virtual void Update(double time);
		virtual void Draw();
	};



	/* BURST PARTICLE CLASS */
	class Burst : public ParticleSystem{
	public:
		Burst();
		Burst(size_t numberOfParticles, SDL_Texture* _particleTextures, float particleSpeed, bool randomSpeeds, bool isRepeating, float frequencyInSeconds);
		Burst(size_t numberOfParticles, std::vector<SDL_Texture*> _particleTextures, float particleSpeed, bool randomSpeeds, bool isRepeating, float frequencyInSeconds);
		float GetFrequency(){ return frequency; }
	private:
		virtual void Setup();
		virtual void Update(double time);
		float frequency;
	};

	/* EMITTER PARTICLE CLASS */
	class Emitter : public ParticleSystem{
	public:
		Emitter();
		Emitter(size_t numberOfParticles, SDL_Texture* texture, bool oneShot, float xDirection, float yDirection);
	private:
		float xDirection, yDirection, timer;
		virtual void Setup();
		virtual void Update(double time);
	};
}
#endif

