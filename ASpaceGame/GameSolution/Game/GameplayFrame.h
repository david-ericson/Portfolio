#pragma once
#include "Engine.h"
#include "Vector2D.h"
#include "ParticleEffect.h"
#include "Spaceship.h"
#include "PlanetMaker.h"
#include "PathedObject.h"
#include "Timer.h"
#include "Profiler.h"
#include "Profile.h"
#include "EnemyShipController.h"
#include "ParticleManager.h"
#include "PlayerHealth.h"
#include "PlayerFuel.h"
#include "CashSystem.h"
#include "Backdrop.h"
#include "Upgrade.h"
#include "HealthPickup.h"
#include "Logger.h"
#include "letterSystem.h"
#include "movingTextManager.h"
#include "DebugMemory.h"

using Core::Input;

static int SCREEN_WIDTH = 1900;
static int SCREEN_HEIGHT = 1040;

//extern char* shipMode = "Wrapping";


static Vector2D fuelStation[] = { 
	Vector2D(1400.0f, 700.0f), Vector2D(1400.0f, 1000.0f), 
	Vector2D(1700.0f, 1000.0f), Vector2D(1700.0f, 700.0f)};

static float debugTime;

extern movingTextManager myText;
static Spaceship ranger(Vector2D(300,400));
static GameObject boundaries(4, fuelStation);
static PlanetMaker creator;
static Timer counter;
static EnemyShipController tester;
extern ParticleManager myParticles;
extern CashSystem myCash;
extern PlayerHealth healthBar;
static PlayerFuel fuelGauge(Vector2D(1820, 350), 30);
extern Backdrop myBackground;
extern Upgrade armorUpgrade;
extern Upgrade healthDropUpgrade;
extern Upgrade fuelUpgrade;
extern Upgrade bulletsUpgrade;
static Vector2D mouse((float)(Core::Input::GetMouseX()), (float)(Core::Input::GetMouseY()));
static letterSystem gameText;
static float pauseToggleCooldown = 0;
extern float totalTime;
extern bool alreadyKilled;
extern bool paused;

class GameplayFrame
{
	HealthPickup healthDrop;
	bool currentFrame;
	bool instructionsPause, upgradesPause;
	float shipDeathTimer;
public:
	GameplayFrame();
	bool UpdateGame(float dt);
	void DrawGame(Core::Graphics& graphics);
	void DebugFrameMemory(Core::Graphics& graphics);
	void setFrame(bool value);
	void resetFrame();
	bool getFrame();
};