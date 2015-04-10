#pragma once
#include "Planet.h"
#include "ParticleEffect.h"
#include "RandomColors.h"

//static ParticleEffect supernova[] = {
//	ParticleEffect(1, Vector2D(950,500), 3000, 500.0f, RGB(255,255,255))};

static Vector2D planetsPoints[] = {
	Vector2D(200.0f, -100.0f), 
	Vector2D(200.0f, 100.0f), 
	Vector2D(0, 200.0f), 
	Vector2D(-200.0f, 100.0f), 
	Vector2D(-200.0f, -100.0f), 
	Vector2D(0, -200.0f)
};

static const int numberPlanetPoints = sizeof(planetsPoints)/sizeof(*planetsPoints);


class PlanetMaker
{
	bool supernova;
public:
	Planet* planets;
	Vector2D* planetPoints;
	RandomColors randColor;
	Core::RGB sunColor;
	Core::RGB planetColor;
	float sunLifespan;
	Randomness myRand;
	int numPlanetPoints;
	bool hasSun;
	PlanetMaker();
	~PlanetMaker();
	void DrawPlanets(Core::Graphics& graphics);
	void UpdatePlanets(float dt);
	void makePlanet(int planetsLeft);
	void resetPlanets();
};