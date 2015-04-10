#pragma once
#include "GameObject.h"

static Vector2D enemyShip[] = {
	Vector2D(0.0f, -20.0f), 
	Vector2D(-20.0f, 10.0f), 
	Vector2D(-10.0f, 20.0f), 
	Vector2D(10.0f, 20.0f), 
	Vector2D(20.0f, 10.0f)};

static Vector2D serpentine[] = {
	Vector2D(700, 50), 
	Vector2D(1100, 250), 
	Vector2D(700, 450),
	Vector2D(1100, 650), 
	Vector2D(700, 850), 
	Vector2D(1100, 1000)}; 

static int pathLinesCount = sizeof(serpentine)/sizeof(*serpentine);

static int shipLinesCount = sizeof(enemyShip)/sizeof(*enemyShip);

class PathedObject: public GameObject
{
public:
	Vector2D* path;
	float beta;
	int startingLine, numPathLines;
	PathedObject();
	void followPath(float dt);
};