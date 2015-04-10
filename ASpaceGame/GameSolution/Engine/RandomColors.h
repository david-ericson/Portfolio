#pragma once
#include "Randomness.h"
#include "Core.h"

class RandomColors
{
	int r,g,b;
	Randomness myRand;
public:
	Core::RGB varyColor(Core::RGB color, int variance);
	Core::RGB brightness(Core::RGB color, float brightValue);
};
