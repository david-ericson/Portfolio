#pragma once
#include <vector>
#include "ParticleEffect.h"
using std::vector;

class ParticleManager
{
	vector<ParticleEffect*> myEffects;
public:
	void addEffect(int effectsType , glm::vec2 origin , int numParticles , float maximumRange, float maximumLifetime);
	void deleteEffect(unsigned int victim);
	void drawEffect();
	void updateEffect(float dt);
	void resetEffects();
};