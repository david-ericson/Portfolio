#pragma once
#include <iostream>
#include <ctime>
#include <cstdio>
#include "Core.h"
#include "Matrix3D.h"
#include "Randomness.h"

const int numPlanets = 5;

class Planet
{
public:
	Vector2D* planetPoints;
	Vector2D position;
	Vector2D parentPosition;
	float angle;
	float scale;
	float orbitDistance;
	int increment;
	int numPlanetPoints;
	void DrawPlanet(Core::Graphics& graphics);
	void UpdatePlanet(float dt, Vector2D parentPosition);
};
