#pragma once
#include "Vector2D.h"
#include "Core.h"

class Particle
{
public:
	Vector2D position, newVelocity, originalVelocity;
	Core::RGB color;
	float lifetime, totalLifetime, size, brightness;
};