#include "ParticleManager.h"

void ParticleManager::addEffect(int effectsType , glm::vec2 origin , int numParticles , float maximumRange, float maximumLifetime)
{
	ParticleEffect* myEffect = new ParticleEffect(effectsType , origin , numParticles , maximumRange, maximumLifetime);
	myEffects.push_back (myEffect);
}

void ParticleManager::deleteEffect(unsigned int victim)
{
	delete myEffects[victim];
	myEffects.erase(myEffects.begin() + victim);
}

void ParticleManager::drawEffect()
{
	for(unsigned int i=0; i<myEffects.size(); i++)
	{
		//myEffects[i]->Draw(graphics);
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

