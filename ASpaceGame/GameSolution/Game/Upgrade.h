#pragma once
#include "Core.h"
#include "Vector2D.h"
#include "CashSystem.h"

static const int BOX_SIZE = 175;
static const float Letter_Size = 15.0f;
static const float Letter_Gap = 5.0f;

static Vector2D armorGraphic[] = {
	Vector2D((float)BOX_SIZE/2, (float)BOX_SIZE/10), Vector2D((float)BOX_SIZE/2+(float)(BOX_SIZE/10), (float)BOX_SIZE/5),
	Vector2D((float)BOX_SIZE/2+(float)(BOX_SIZE/5), (float)(BOX_SIZE/10)), Vector2D((float)BOX_SIZE/2+(float)(BOX_SIZE/5), (float)BOX_SIZE/10+(float)3*(BOX_SIZE/10)),
	Vector2D((float)BOX_SIZE/2, (float)(BOX_SIZE/2)), Vector2D((float)BOX_SIZE/2-(float)(BOX_SIZE/5), (float)BOX_SIZE/10+(float)3*(BOX_SIZE/10)),
	Vector2D((float)BOX_SIZE/2-(float)(BOX_SIZE/5), (float)(BOX_SIZE/10)), Vector2D((float)(BOX_SIZE/2)-(float)(BOX_SIZE/10), (float)(BOX_SIZE/5))
};

static Vector2D fuelGraphic[] = {
	Vector2D((float)BOX_SIZE/4, (float)BOX_SIZE/10), Vector2D((float)BOX_SIZE/2+(float)BOX_SIZE/10,(float)BOX_SIZE/10),
	Vector2D((float)3*(BOX_SIZE/4), (float)BOX_SIZE/5), Vector2D((float)3*(BOX_SIZE/4), (float)BOX_SIZE/2),
	Vector2D((float)BOX_SIZE/4, (float)BOX_SIZE/2)
};

static Vector2D healthGraphic[] = {
	Vector2D((float)BOX_SIZE/4+(float)BOX_SIZE/20, (float)BOX_SIZE/4), Vector2D((float)BOX_SIZE/2-(float)BOX_SIZE/20, (float)BOX_SIZE/4),
	Vector2D((float)BOX_SIZE/2-(float)BOX_SIZE/20, (float)BOX_SIZE/10), Vector2D((float)BOX_SIZE/2+(float)BOX_SIZE/20, (float)BOX_SIZE/10),
	Vector2D((float)BOX_SIZE/2+(float)BOX_SIZE/20, float(2.5)*(float)BOX_SIZE/10), Vector2D((float)BOX_SIZE/2+(float)BOX_SIZE/4-(float)BOX_SIZE/20, (float(2.5)*(float)BOX_SIZE/10)),
	Vector2D((float)BOX_SIZE/2+(float)BOX_SIZE/4-(float)BOX_SIZE/20, (float)BOX_SIZE/4+(float)BOX_SIZE/10), Vector2D((float)BOX_SIZE/2+(float)BOX_SIZE/20, (float)BOX_SIZE/4+(float)BOX_SIZE/10), 
	Vector2D((float)BOX_SIZE/2+(float)BOX_SIZE/20, (float)BOX_SIZE/2), Vector2D((float)BOX_SIZE/2-(float)BOX_SIZE/20, (float)BOX_SIZE/2),
	Vector2D((float)BOX_SIZE/2-(float)BOX_SIZE/20, (float)BOX_SIZE/4+(float)BOX_SIZE/10), Vector2D((float)BOX_SIZE/4+(float)BOX_SIZE/20, (float)BOX_SIZE/4+(float)BOX_SIZE/10)
};

static Vector2D bulletGraphic[] = {
	Vector2D((float)BOX_SIZE/2-(float)3*(BOX_SIZE/10), (float)(BOX_SIZE/2 - BOX_SIZE/10)/2), Vector2D((float)BOX_SIZE/2-(float)(BOX_SIZE/5), (float)(BOX_SIZE/10)),
	Vector2D((float)BOX_SIZE/2+(float)(BOX_SIZE/5), (float)(BOX_SIZE/10)), Vector2D((float)BOX_SIZE/2+(float)(BOX_SIZE/5),  (float)(BOX_SIZE/2 - BOX_SIZE/10)/2+(float)BOX_SIZE/10),
	Vector2D((float)BOX_SIZE/2-(float)(BOX_SIZE/5), (float)(BOX_SIZE/2 - BOX_SIZE/10)/2+(float)BOX_SIZE/10)
};

static const int armorSize = sizeof(armorGraphic)/sizeof(*armorGraphic);
static const int fuelSize = sizeof(fuelGraphic)/sizeof(*fuelGraphic);
static const int healthSize = sizeof(healthGraphic)/sizeof(*healthGraphic);
static const int bulletSize = sizeof(bulletGraphic)/sizeof(*bulletGraphic);

extern CashSystem myCash;

class Upgrade
{
	Core::RGB myColor;
	const char* text;
	Vector2D position, costPosition;
	int upgradeCount;
	float upgradeCost, upgradeCooldown;
	int type;
	bool atTheDot;
public:
	enum upgrades{ armor, fuel, health, bullet};
	Upgrade(const char* info, Vector2D startPosition, int upgradeType);
	void DrawUpgrade(Core::Graphics& graphics, Vector2D mouse, float thickness);
	void DrawHorizontalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition);
	void DrawGraphicPoints(Core::Graphics& graphics, Vector2D* points, int numPoints);
	void DrawVerticalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition);
	void DrawDiagonalBar(Core::Graphics& graphics, float thickness, Vector2D endPositionq, Vector2D startPosition);
	void DrawLetters(Core::Graphics& graphics, float thickness);
	void DrawGraphic(Core::Graphics& graphics);
	void resetUpgrade();
	void viewText(Core::Graphics& graphics);
	void SetUpgradeCost();
	int getUpgradeCount();
	bool CheckMouse(Vector2D mouse);
};