#include "CashSystem.h"
#include <cstdio>

CashSystem::CashSystem(Vector2D startingPosition)
{
	position = startingPosition;
	cash = 200;
}

void CashSystem::DrawCash(Core::Graphics& graphics, float thickness)
{
	char buf[50];
	sprintf_s(buf, "Cash Money:$%i", (int)cash);
	drawCash.drawText(graphics, thickness, RGB(89, 255, 92), buf, 30.0f, 5.0f, 0, position);
}

void CashSystem::DrawHorizontalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x, startPosition.y + i);
		Vector2D end(startPosition.x + size, startPosition.y+i);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void CashSystem::DrawVerticalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x + i, startPosition.y);
		Vector2D end(startPosition.x + i, startPosition.y+size);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void CashSystem::increaseCash(float increment)
{
	cash += increment;
}

void CashSystem::decreaseCash(float decrement)
{
	cash -= decrement;
}

void CashSystem::resetCash()
{
	cash = 300;
}

float CashSystem::getCash()
{
	return cash;
}
