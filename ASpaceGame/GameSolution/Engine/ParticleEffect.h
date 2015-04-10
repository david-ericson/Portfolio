#pragma once
#include "RandomColors.h"
#include "ExportHeader.h"
#include "Matrix3D.h"
#include "Particle.h"

class ParticleEffect
{
public:
	Particle* particles;
	RandomColors randColor;
	Randomness random;
	Vector2D startPos;
	int numberParticles;
	int effectType;
	float angle;
	bool anyAlive;
	ParticleEffect(int effectsType , Vector2D origin , int numParticles , float maximumRange, float maximumLifetime, Core::RGB color );
	~ParticleEffect();
	void Update(float dt);
	void setNewOrigin(Vector2D newOrigin);
	void CheckandCreateNewParticles( Vector2D position, float angle);
	void Draw(Core::Graphics& graphics);
};