#pragma once
#include <stdlib.h>
#include "Vector2D.h"
#include <cmath>
#include <ctime>
#include "Engine.h"

const float TWO_PI = 2 * 3.1415926f;

class Randomness
{
public:
	Randomness();
	float randomFloat();
	Vector2D randomUnitVector();
	float randomInRange(float min, float max);
};