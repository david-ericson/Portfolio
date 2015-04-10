#include "Vector2D.h"
#include "Core.h"
#include "Upgrade.h"
#include "letterSystem.h"
#include "RandomColors.h"

static const float INCREMENT_PER_SECOND = 20.0f;
static const float MAX_FUEL = 100.0f;

extern Upgrade fuelUpgrade;

class PlayerFuel
{
	RandomColors randColor;
	letterSystem fuelWarning;
	letterSystem fuelBar;
	Vector2D fuelBarPosition;
	const char* warningText;
	float fuelAmount, decrementPerSecond, fadingTime, barWidth;
	bool fadingIn;
public:
	PlayerFuel(Vector2D startPosition, float thickness);
	void DrawPlayerFuel(Core::Graphics& graphics);
	void UpdateFuel(float dt, bool fueling);
	void increaseFuel(float increment);
	void decreaseFuel(float decrement);
	void resetFuel();
	float getFuel();
};