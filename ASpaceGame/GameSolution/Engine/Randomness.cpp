#include "Randomness.h"

Randomness::Randomness()
{
	srand ((unsigned int)time(NULL));
}

 float Randomness::randomFloat()
{
	return (float) rand()/RAND_MAX;
}

 Vector2D Randomness::randomUnitVector()
{
	float angle = TWO_PI * randomFloat();
	return Vector2D(cos(angle), sin(angle));
}

 float Randomness::randomInRange(float min, float max)
{
	return (randomFloat()*(max-min+1)+min);
}