#pragma once
#include "Vector2D.h"
#include "Core.h"

class Shape
{
public:
	Vector2D* points;
	int numLines;
	Shape(){}
	Shape(int lines, Vector2D* pointer);
	void Draw(Core::Graphics& graphics, Vector2D position);
	Vector2D getSmallestValues();
	Vector2D getLargestValues();
};