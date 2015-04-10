#pragma once
#include "Vector2D.h"
#include "Core.h"

struct letterSystem
{
	void drawText(Core::Graphics& graphics, float thickness, Core::RGB color, const char* text, float size, float gap, int currentLet, Vector2D position);
	void DrawHorizontalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition);
	void DrawVerticalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition);
	void DrawDiagonalBar(Core::Graphics& graphics, float thickness, Vector2D startPosition, Vector2D endPosition);
	void DrawDiagonalBarX(Core::Graphics& graphics, float thickness, Vector2D startPosition, Vector2D endPosition);
};