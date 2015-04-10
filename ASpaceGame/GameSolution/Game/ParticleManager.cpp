#include "ParticleManager.h"


void ParticleManager::addEffect(int effectsType , Vector2D origin , int numParticles , float maximumRange, float maximumLifetime, Core::RGB color)
{
	ParticleEffect* myEffect = new ParticleEffect(effectsType , origin , numParticles , maximumRange, maximumLifetime,  color);
	myEffects.push_back (myEffect);
}

void ParticleManager::deleteEffect(unsigned int victim)
{
	delete myEffects[victim];
	myEffects.erase(myEffects.begin() + victim);
}

void ParticleManager::drawEffect(Core::Graphics& graphics)
{
	for(unsigned int i=0; i<myEffects.size(); i++)
	{
		myEffects[i]->Draw(graphics);
	}
}

void ParticleManager::updateEffect(float dt)
{
	for(unsigned int i=0; i<myEffects.size(); i++)
	{
		myEffects[i]->Update(dt);
		if(!myEffects[i]->anyAlive)
		{
			deleteEffect(i);
			i--;
		}
	}
}

void ParticleManager::resetEffects()
{
	for(unsigned int i=0; i<myEffects.size(); i)
	{
		deleteEffect(0);
	}
}

