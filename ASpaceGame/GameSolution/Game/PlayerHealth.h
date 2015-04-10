#pragma once
#include "Core.h"
#include "Vector2D.h"
#include "Upgrade.h"
#include "letterSystem.h"
#include "RandomColors.h"

static const float MAX_HEALTH = 100.0f;

extern Upgrade armorUpgrade;
extern bool paused;

class PlayerHealth
{
	letterSystem healthBarText;
	RandomColors randomColors;
	Vector2D position;
	float healthLeft, thickness, armor, armorRegen, timeSinceLastDamage;
public:
	PlayerHealth(Vector2D startPosition, float size);
	void DrawHealth(Core::Graphics& graphics);
	void DrawArmor(Core::Graphics& graphics);
	void UpdateArmor(float dt);
	void increaseHealth(float amount);
	void decreaseHealth(float amount);
	void resetHealth();
	float getHealth();
};