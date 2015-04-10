#include "PlayerHealth.h"

PlayerHealth::PlayerHealth(Vector2D startPosition, float size)
{
	thickness = size;
	position = startPosition;
	timeSinceLastDamage = 0;
	armor = 0;
	healthLeft = 100.0f;
}

void PlayerHealth::DrawHealth(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(0, 255, 0));
	healthBarText.drawText(graphics, 3.0f, RGB(0, 255, 0), "HEALTH", 17.0f, 3.0f, 0, Vector2D(position.x - 40, position.y -30));
	for(int i=0; i<(int(thickness)); i++)
	{
		//Draws remaining health and sets color
		if(healthLeft >= MAX_HEALTH/2)
		{
			graphics.SetColor(RGB((MAX_HEALTH - healthLeft) * 5, 255, 0));
		}
		else
		{
			graphics.SetColor(RGB(255,255 - ((( MAX_HEALTH-healthLeft)*5)-250), 0));
		}
		Vector2D start(i + position.x, position.y);
		Vector2D end(i+position.x, position.y + healthLeft*5);
		graphics.DrawLine(start.x, start.y, end.x, end.y);

		//Draws the unfilled portion of the bar
		graphics.SetColor(RGB(25,25,25));
		Vector2D totalStart(i+position.x, end.y);
		Vector2D totalEnd(i+position.x, end.y + ((MAX_HEALTH - healthLeft)*5));
		graphics.DrawLine(totalStart.x, totalStart.y, totalEnd.x, totalEnd.y);
	}
	DrawArmor(graphics);
}

void PlayerHealth::DrawArmor(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(179, 252, 234));
	for(int i=0; i<int(thickness); i++)
	{
		Vector2D start(i + position.x, position.y);
		Vector2D end(i+position.x, position.y + armor*5);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void PlayerHealth::UpdateArmor(float dt)
{
	armorRegen = float(armorUpgrade.getUpgradeCount());
	if(timeSinceLastDamage >= 5&& !paused)
	{
		if(armor < healthLeft)
			armor += armorRegen*dt;
	}
	else
	{
		timeSinceLastDamage += dt;
	}

}

void PlayerHealth::increaseHealth(float amount)
{
	healthLeft = (healthLeft + amount > MAX_HEALTH) ? MAX_HEALTH: healthLeft + amount;
}

void PlayerHealth::decreaseHealth(float amount)
{
	armor -= amount;
	if(armor <= 0)
	{
		healthLeft = (healthLeft + armor < 0) ? 0: healthLeft + armor;
		armor = 0;
	}
	timeSinceLastDamage = 0;
}

float PlayerHealth::getHealth()
{
	return healthLeft;
}

void PlayerHealth::resetHealth()
{
	timeSinceLastDamage = 0;
	armor = 0;
	healthLeft = 100.0f;
}

