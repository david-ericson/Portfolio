#include "GameplayFrame.h"
#include "OpeningFrame.h"
#include "Backdrop.h"
#include "Assert.h"
#include "letterSystem.h"
#include "DebugMemory.h"
#include <malloc.h>

using Core::Input;

ParticleManager myParticles;
movingTextManager myText;
CashSystem myCash(Vector2D(600.0f, 20.0f));
PlayerHealth healthBar(Vector2D(50, 350), 30);
Upgrade armorUpgrade("ARMOR", Vector2D(350.0f, 400.0f), 0);
Upgrade healthDropUpgrade("HEALTH", Vector2D(650.0f, 400.0f), 2);
Upgrade fuelUpgrade("FUEL", Vector2D(1250.0f, 400.0f), 1);
Upgrade bulletsUpgrade("TURRET", Vector2D(950.0f, 400.0f), 3);
Backdrop myBackground(SCREEN_WIDTH, SCREEN_HEIGHT);
letterSystem myLetters;
float totalTime;
bool paused = false;
bool initialized = false;
bool alreadyKilled = false;

OpeningFrame startFrame;
GameplayFrame gameFrame;

bool update(float dt)
{
	bool result = false;
	if(gameFrame.getFrame())
	{
		if(!initialized)
		{
			profiler.initialize("profiles.csv");
			initialized = true;
			LOG(Info, "Profiler was initialized");
		}
		result = gameFrame.UpdateGame(dt);
	}
	else
	{
		ASSERT(startFrame.getIsCurrentFrame(), "Neither frame is running");
		startFrame.UpdateFrame(Vector2D((float)(Core::Input::GetMouseX()), (float)(Core::Input::GetMouseY())), dt);
	}
	return result;
}

void drawFunction(Core::Graphics& graphics)
{	
	if(gameFrame.getFrame())
	{
		char buf[50];
		sprintf_s(buf, "Total Time: %i", (int)totalTime);
		gameFrame.DrawGame(graphics);
		myLetters.drawText(graphics, 4.0f, RGB(255,255,255), buf, 25.0f, 3.0f, 0, Vector2D(20, 25));
	}
	else
	{
		startFrame.DrawFrame(graphics);
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	Core::Init("Spaceship", SCREEN_WIDTH, SCREEN_HEIGHT);
	LOG(Info, "Program has started to run");
	LOG(Warning, "Unreferenced formal parameter dt");
	LOG(Error, "Example error message");  

	Core::RegisterUpdateFn(update);
	Core::RegisterDrawFn(drawFunction);
	Core::GameLoop();
	LOG(Info, "GameLoop has finished running");
	myParticles.resetEffects();
	myText.resetText();
	if(initialized)
	{
		profiler.shutdown();
		LOG(Info, "Profiler has shutdown");
	}
	ASSERT(initialized, ": Profiler failed to initialize");
	END_LOG
}