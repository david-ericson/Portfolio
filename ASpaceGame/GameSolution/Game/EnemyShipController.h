#pragma once
#include "EnemyShip.h"
#include "Randomness.h"
#include "letterSystem.h"

static const int NUM_MAX_SHIPS = 50;
static float spawnRate = 3.0f;

extern float totalTime;

class EnemyShipController
{
	EnemyShip* enemies;
	Randomness myRand;
	letterSystem gameAlerts;
	float timeFromLastSpawn, startingPause;
	bool firstWarningShown, secondWarningShown;
public:
	EnemyShipController();
	~EnemyShipController();
	void drawShips(Core::Graphics& graphics);
	void updateShips(float dt, Vector2D& shipPosition, Bullets* bullets, int numBullets);
	void resetShips();
};