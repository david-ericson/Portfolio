#pragma once
#include <stdlib.h>
#include <cmath>
#include <glm\glm.hpp>
#include <ctime>
#include <Engine.h>

const float TWO_PI = 2 * 3.1415926f;

class Randomness
{
public:
	ENGINE_SHARED Randomness();
	ENGINE_SHARED float randomFloat();
	ENGINE_SHARED glm::vec2 randomUnitVector();
	ENGINE_SHARED float randomInRange(float min, float max);
};