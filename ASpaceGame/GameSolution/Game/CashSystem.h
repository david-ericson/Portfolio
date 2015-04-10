#pragma once
#include "Core.h"
#include "Vector2D.h"
#include "letterSystem.h"

static const float LETTER_SIZE = 50.0f;
static const float LETTER_GAP = 10.0f;

class CashSystem
{
	letterSystem drawCash;
	Vector2D position;
	int currentLetter;
	float cash;
	bool atTheDot;
public:
	CashSystem(Vector2D startingPosition);
	void DrawCash(Core::Graphics& graphics, float thickness);
	void DrawHorizontalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition);
	void DrawVerticalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition);
	void DrawNumbers(Core::Graphics& graphics, float thickness);
	void increaseCash(float increment);
	void decreaseCash(float decrement);
	void resetCash();
	float getCash();
};