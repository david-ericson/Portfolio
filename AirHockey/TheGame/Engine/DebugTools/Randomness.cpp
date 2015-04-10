#include <DebugTools\Randomness.h>

Randomness::Randomness()
{
	//srand ((unsigned int)time(NULL));
}

 float Randomness::randomFloat()
{
	return (float) rand()/RAND_MAX;
}

 glm::vec2 Randomness::randomUnitVector()
{
	float angle = TWO_PI * randomFloat();
	return glm::vec2(cos(angle), sin(angle));
}

 float Randomness::randomInRange(float min, float max)
{
	return (randomFloat()*(max-min)+min);
}