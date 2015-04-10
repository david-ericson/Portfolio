#pragma once
#include <glm\glm.hpp>
#include "Core.h"

class Particle
{
public:
	glm::vec2 position, newVelocity, originalVelocity;
	Core::RGB color;
	float lifetime, totalLifetime, size, brightness;
};