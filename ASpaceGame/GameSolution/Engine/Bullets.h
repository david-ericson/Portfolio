#pragma once
#include "Core.h"
#include "Vector2D.h"
#include "Matrix3D.h"

static const int bulletSpeed = 750;

static Vector2D ammo[] = {
	Vector2D(-2.0f, -2.0f), 
	Vector2D(-2.0f, 2.0f),
	Vector2D(4.0f, 2.0f), 
	Vector2D(5.0f, 0), 
	Vector2D(4.0f, -2.0f)};

static const int numberOfBulletPoints = sizeof(ammo)/sizeof(*ammo);

class Bullets
{
	Vector2D position;
	Vector2D velocity;
	float angle, damage;
public:
	bool alive;
	Bullets();
	void drawBullet(Core::Graphics& graphics, Matrix3D transform);
	bool isBulletOnScreen(int SCREEN_HEIGHT, int SCREEN_WIDTH);
	void setVelocity(Vector2D newVelocity);
	void setPosition(Vector2D newPosition);
	void setAngle(float radians);
	Vector2D getPosition();
	float getAngle();
	float getDamage();
	void moveBullet(float dt);
	void resetBullet(float sentinel_value);
};