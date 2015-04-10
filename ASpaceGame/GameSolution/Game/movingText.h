#pragma once
#include "Core.h"
#include "Vector2D.h"
#include "letterSystem.h"

class movingText
{
	letterSystem myText;
	Vector2D velocity;
	Vector2D position;
	const char* text;
	Core::RGB textColor;
	float life, thickness, size, gap;
public:
	movingText(float myThickness, Core::RGB color, const char* myText, float letter_size, float letter_gap, float lifeTime, Vector2D startPosiion);
	void drawText(Core::Graphics& graphics);
	void updateText(float dt);
	bool lifetimeIsOver();
};

