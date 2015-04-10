#pragma once
#include "Core.h"
#include "Vector2D.h"
#include "Randomness.h"
#include "PlayerHealth.h"
#include "Upgrade.h"


static float distance;

static Vector2D wrenchPoints[] = {
	Vector2D(0, -5.0f), Vector2D(0, -15.0f), Vector2D(5.0f, -20.0f),
	Vector2D(5.0f, -10.0f), Vector2D(10.0f, -8.0f), Vector2D(15.0f, -10.0f),
	Vector2D(15.0f, -20.0f), Vector2D(20.0f, -15.0f), Vector2D(20.0f, -6.0f),
	Vector2D(5.0f, -3.0f), Vector2D(-5.0f, 15.0f), Vector2D(-8.0f, 17.0f),
	Vector2D(-11.0f, 14.0f)};

extern PlayerHealth healthBar;
extern Upgrade healthDropUpgrade;
extern bool paused;

static const int numWrenchPoints = sizeof(wrenchPoints)/sizeof(*wrenchPoints);

class HealthPickup
{
	Randomness myRand;
	Vector2D position;
	float lifetime, healAmount, spawnIncrement, lastUpgradeCount;
	bool alive, setIncrement;
public:
	HealthPickup();
	void DrawHealthPickup(Core::Graphics& graphics);
	void UpdateHealthPickup(float dt, Vector2D& shipPosition);
	void bringToLife();
	bool getLife();
	void checkLife(float dt);
	void resetHealthDrop();
};