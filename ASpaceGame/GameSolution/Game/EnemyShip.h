#pragma once
#include "Vector2D.h"
#include "Bullets.h"

extern float totalTime;

static Vector2D standardEnemyPoints[] =
{
	Vector2D(-6.0f,-15.0f), Vector2D(-21.0f, 0),
	Vector2D(-6.0f, 15.0f), Vector2D(21.0f, 0)
};

static Vector2D strongEnemyPoints[] =
{
	Vector2D(-30.0f,-30.0f), Vector2D(-45.0f, -15.0f), Vector2D(-45.0f,15.0f),
	Vector2D(-30.0f,30.0f), Vector2D(45.0f, 30.0f), Vector2D(45.0f,15.0f),
	Vector2D(15.0f,15.0f), Vector2D(15.0f, -15.0f), Vector2D(45.0f,-15.0f),
	Vector2D(45.0f,-30.0f), Vector2D(-30.0f, -30.0f)
};
static const int NUM_STNDR_POINTS = sizeof(standardEnemyPoints)/ sizeof(*standardEnemyPoints);
static const int NUM_STRONG_POINTS = sizeof(strongEnemyPoints)/ sizeof(*strongEnemyPoints);

class EnemyShip
{
	Vector2D velocity;
	Vector2D position;
	float angle, worth, damage;
	float noCrashingTimer, maxHealth, health, hitRadius;
	int enemyType;
	bool alive;
public:
	bool playParticle;
	EnemyShip();
	void draw(Core::Graphics& graphics);
	void drawShip(Core::Graphics& graphics);
	void update(float dt, const Vector2D& shipPosition, Bullets* bullets, int numBullets);
	void checkDeath(Bullets* thisBullet);
	void resetShip();
	void setPosition(Vector2D newPosition);
	void bringToLife(int type);
	void resetParticleLifetime();
	Vector2D getPosition();
	bool isParticlePlaying();
	bool isShipAlive();
};