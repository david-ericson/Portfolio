#pragma once
#include "Core.h"
#include "Vector2D.h"
#include "Randomness.h"
#include "RandomColors.h"
#include "Particle.h"
#include "Matrix3D.h"

static Vector2D asteroidPoints[] = {
	Vector2D(-20.0f, 0), Vector2D(-10.0f, -10.0f),
	Vector2D(10.0f, -10.0f), Vector2D(20.0f, 0),
	Vector2D(10.0f, 10.0f), Vector2D(-10.0f, 10.0f)};

const static int NUM_STARS = 120;
const static int NUM_ASTEROID_POINTS = (sizeof(asteroidPoints)/sizeof(*asteroidPoints));
static float debugAsteroid;

class Backdrop
{
	Particle* particles;
	RandomColors randomColor;
	Vector2D asteroidPosition, asteroidVelocity;
	Randomness myRand;
	float asteroidRespawn, angle, screen_width, screen_height;
	bool asteroidVisible;
public:
	Backdrop(int width, int height);
	~Backdrop();
	void DrawBackdrop(Core::Graphics& graphics);
	void UpdateAsteroid(float dt);
	bool isAsteroidOnScreen();
};