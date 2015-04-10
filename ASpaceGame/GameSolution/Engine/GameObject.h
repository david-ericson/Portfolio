#pragma once
#include "Shape.h"

class GameObject
{
public:
	Vector2D position;
	Vector2D velocity;
	Shape shape;
	GameObject(int numLines, Vector2D* outline) : shape(numLines, outline){}
	void Draw(Core::Graphics& graphics);
};