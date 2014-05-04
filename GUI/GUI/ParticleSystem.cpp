#include "ParticleSystem.h"
using namespace GuiAPI;

/* Default Particle System */
ParticleSystem::ParticleSystem(){};
ParticleSystem::~ParticleSystem(){};

void ParticleSystem::SetPosition(float x, float y)
{
	for (size_t i = 0; i < particleList.size(); i++)
	{
		particleList.at(i)->SetOriginalPosition(x, y);
		particleList.at(i)->SetPosition(x, y);
	}
}
void ParticleSystem::SetSpeed(float _speed)
{
	particleSpeed = _speed;
}
void ParticleSystem::Initialize(size_t particleNum)
{
	for (size_t i = 0; i < particleNum; i++)
	{
		for (size_t k = 0; k < m_ParticleTextures.size(); k++)
		{
			if (m_ParticleTextures.at(k) != nullptr)
			{
				Particle* myParticle = new Particle(m_ParticleTextures.at(k));
				particleList.push_back(myParticle);
			}
		}
	}
}

void ParticleSystem::Draw()
{
	if (Active)
	{
		rect.x += offset.x + padding.x;
		rect.y += offset.y + padding.y;
		for (size_t i = 0; i < particleList.size(); i++)
		{
			if (particleList.at(i)->isAlive())
				particleList.at(i)->Draw();
		}
	}
}
void ParticleSystem::Update(double time){}
void ParticleSystem::Setup(){}

/* Burst Particle System */
Burst::Burst(){};
Burst::Burst(size_t numberOfParticles, SDL_Texture* _particleTextures, float particleSpeed, bool randomSpeeds, bool isRepeating, float frequencyInSeconds)
{
	SetTexture(_particleTextures);
	SetRepeat(isRepeating);
	SetSpeed(particleSpeed);
	SetRandom(randomSpeeds);
	frequency = frequencyInSeconds;
	ParticleSystem::Initialize(numberOfParticles);
	Setup();
}
Burst::Burst(size_t numberOfParticles, std::vector<SDL_Texture*> _particleTextures, float particleSpeed, bool randomSpeeds, bool isRepeating, float frequencyInSeconds)
{
	SetTextures(_particleTextures);
	SetRepeat(isRepeating);
	SetSpeed(particleSpeed);
	SetRandom(randomSpeeds);
	frequency = frequencyInSeconds;
	ParticleSystem::Initialize(numberOfParticles);
	Setup();
}
void Burst::Update(double time)
{
	bool particleListOccupied = false;
	if (Active)
	{
		if (particleList.size() != 0)
		{
			for (size_t i = 0; i < particleList.size(); i++)
			{
				if (particleList.at(i)->isAlive())
				{
					particleListOccupied = true;
					particleList.at(i)->Update(time);
				}
				else if (isRepeating())
				{
					particleList.at(i)->ResetParticle(); //Reset the particle

					if (isRandomSpeeds())
						particleList.at(i)->SetSpeed((rand() % 20) + 5.0f); //Set a new random speed
				}

			}
		}
	}
	if (!isRepeating())
	{
		if (!particleListOccupied)
		{
			particleList.clear();
			Active = false;
		}
	}
}
void Burst::Setup()
{
	//Set the direction of each particle
	for (size_t i = 0; i < particleList.size(); i++)
	{
		float inDegrees = 360.0f / (int)particleList.size();
		float inRadians = inDegrees * (180 / 3.14f);

		if (!isRandomSpeeds())
			particleList.at(i)->SetSpeed(GetSpeed());
		else
			particleList.at(i)->SetSpeed(rand() % 20 + 5.0f);

		particleList.at(i)->SetAlphaTimer(GetFrequency());
		particleList.at(i)->SetDirection(sin(inRadians*i), cos(inRadians*i));
	}

}


/* Emitter Particle System */
Emitter::Emitter(){};
Emitter::Emitter(size_t numberOfParticles, SDL_Texture* texture, bool isRepeating, float _xDirection, float _yDirection)
{
	timer = 0;
	SetTexture(texture);
	SetRepeat(isRepeating);
	SetRandom(true);

	xDirection = _xDirection;
	yDirection = _yDirection;

	ParticleSystem::Initialize(numberOfParticles);
	Setup();
}

void Emitter::Update(double time)
{
	bool particleListOccupied = false;
	if (Active)
	{
		if (particleList.size() != 0)
		{
			for (size_t i = 0; i < particleList.size(); i++)
			{
				if (particleList.at(i)->isAlive())
				{
						particleListOccupied = true;
						particleList.at(i)->Update(time);
				}
				else if (isRepeating())
				{
					particleList.at(i)->ResetParticle(); //Reset the particle
					particleList.at(i)->SetSpeed((rand() % 20) + 5.0f); //Set a new random speed
					particleList.at(i)->SetPosition(rand() % (GetPosition().x + 1) + 10.0f,
													rand() % (GetPosition().y + 1) + 10.0f);
				}

			}
		}
	}
	else if (!isRepeating())
	{
		if (!particleListOccupied)
		{
			particleList.clear();
			Active = false;
		}
	}
}


void Emitter::Setup()
{
	for (size_t i = 0; i < particleList.size(); i++)
	{
		if (!isRandomSpeeds())
			particleList.at(i)->SetSpeed(GetSpeed());
		else
			particleList.at(i)->SetSpeed(rand() % 5 + 5.0f);

		particleList.at(i)->SetPosition(rand() % (GetPosition().x+5) + 10.0f,
										rand() % (GetPosition().y+15) + 10.0f);


		particleList.at(i)->SetDirection(xDirection, yDirection);
	}
}

