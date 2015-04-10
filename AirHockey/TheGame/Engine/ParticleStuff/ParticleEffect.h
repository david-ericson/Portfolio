#pragma once
#include <DebugTools\RandomColors.h>
#include <ExportHeader.h>
#include <glm\glm.hpp>
#include "Particle.h"

class ParticleEffect
{
public:
	Particle* particles;
	RandomColors randColor;
	Randomness random;
	glm::vec2 startPos;
	int numberParticles;
	int effectType;
	float angle;
	bool anyAlive;
	ParticleEffect(int effectsType , glm::vec2 origin , int numParticles , float maximumRange, float maximumLifetime);
	~ParticleEffect();
	void Update(float dt);
	void setNewOrigin(glm::vec2 newOrigin);
	void CheckandCreateNewParticles( glm::vec2 position, float angle);
	void Draw();
};