#pragma once
#include <vector>
#include "ParticleEffect.h"
using std::vector;

class ParticleManager
{
	vector<ParticleEffect*> myEffects;
public:
	void addEffect(int effectsType , Vector2D origin , int numParticles , float maximumRange, float maximumLifetime, Core::RGB color);
	void deleteEffect(unsigned int victim);
	void drawEffect(Core::Graphics& graphics);
	void updateEffect(float dt);
	void resetEffects();
};