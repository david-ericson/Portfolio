#include "PlayerFuel.h"

extern bool alreadyKilled;

PlayerFuel::PlayerFuel(Vector2D startPosition, float thickness)
{
	fuelAmount = MAX_FUEL;
	barWidth = thickness;
	fuelBarPosition = startPosition;
	fadingTime = 1.0f;
	fadingIn = true;
}

void PlayerFuel::DrawPlayerFuel(Core::Graphics& graphics)
{
	Core::RGB myColor = RGB(168,175,34);

	fuelBar.drawText(graphics, 3.0f, myColor, "FUEL", 17.0f, 3.0f, 0, Vector2D(fuelBarPosition.x-17, fuelBarPosition.y-30));
	for(int i=0; i<(int(barWidth)); i++)
	{
		graphics.SetColor(RGB(168, 175, 34));
		Vector2D start(i + fuelBarPosition.x, fuelBarPosition.y);
		Vector2D end(i+fuelBarPosition.x, fuelBarPosition.y + fuelAmount*5);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
		graphics.SetColor(RGB(25,25,25));
		Vector2D totalStart(i+fuelBarPosition.x, end.y);
		Vector2D totalEnd(i+fuelBarPosition.x, end.y + ((MAX_FUEL - fuelAmount)*5));
		graphics.DrawLine(totalStart.x, totalStart.y, totalEnd.x, totalEnd.y);
	}
	if(fuelAmount <= 50.0f && !alreadyKilled)
	{
		Core::RGB textColor = randColor.brightness(RGB(175, 175, 0), 1.0f - (fadingTime));
		warningText = "MEDIUM FUEL";
		if(fuelAmount <= 25.0f)
		{
			textColor = randColor.brightness(RGB(175, 0, 0), 1.0f - (fadingTime));
			warningText = "LOW FUEL!!!";
		}
		fuelWarning.drawText(graphics, 10.0f, textColor, warningText, 40.0f, 5.0f, 0, Vector2D(650.0f, 250.0f));
	}
	else
	{
		fadingTime = 1.0f;
		fadingIn = true;
	}
}

void PlayerFuel::UpdateFuel(float dt, bool fueling)
{
	if(fuelAmount <= 50.0f)
	{
		if(fadingTime > 0 && fadingIn)
		{
			fadingTime -= dt;
			if(fadingTime <= 0)
			{
				fadingIn = false;
			}
		}
		else if(fadingTime < 1.0f && !fadingIn)
		{
			fadingTime += dt;
			if(fadingTime >= 1.0f)
			{
				fadingIn = true;
			}
		}
	}
	decrementPerSecond = 6.0f - fuelUpgrade.getUpgradeCount();
	if(!fueling)
	{
		decreaseFuel((float)decrementPerSecond * dt);
	}
	else
	{
		increaseFuel((float)INCREMENT_PER_SECOND * dt);
	}
}

void PlayerFuel::increaseFuel(float increment)
{
	fuelAmount = (fuelAmount + increment > MAX_FUEL) ? MAX_FUEL: fuelAmount + increment;
}

void PlayerFuel::decreaseFuel(float decrement)
{
	fuelAmount = (fuelAmount - decrement < 0) ? 0 : fuelAmount - decrement;
}

void PlayerFuel::resetFuel()
{
	fuelAmount = MAX_FUEL;
}

float PlayerFuel::getFuel()
{
	return fuelAmount;
}