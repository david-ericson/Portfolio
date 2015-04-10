#include <Qt\qapplication.h>
#include <Engine.h>
#include <DebugTools\DebugShapesManager.h>
#include <DebugTools\Timer.h>
#include <LightManager.h>
#include <MirrorManager.h>
#include <DebugTools\DebugMenus.h>
#include <DebugTools\DebugMemory.h>
#include <malloc.h>
#include "Puck.h"
#include "WallManager.h"
#include "DebugTools\Profiler.h"
#include "PlayerManager.h"
#define _CRTDBG_MAP_ALLOC

Timer t;
Puck puck;

void update()
{
	float time = t.getLastTimeIntervalDT();
	time;
	DebugMenus::update();
	LightManager::update(time);
	WallManager::checkCollisions(&puck);
	PlayerManager::update();
	puck.update();
}

void shutdown()
{
	DebugMenus::shutdown();
	LightManager::shutdown();
	Engine::shutdown();
	WallManager::shutdown();
	PlayerManager::shutdown();
	GeneralGLWindow::shutdown();
	
}

void createWalls()
{
	WallManager::addWall(glm::vec3(7,-2.0f,0), glm::vec3(1.0f,1,22),glm::vec3());
	WallManager::addWall(glm::vec3(-7,-2.0f,0), glm::vec3(1.0f,1,22),glm::vec3());
	WallManager::addWall(glm::vec3(-4.75f,-2.0f,10.5f), glm::vec3(1,1,4.5),glm::vec3(0, 90.0f, 0));
	WallManager::addWall(glm::vec3(4.75f,-2.0f,10.5f), glm::vec3(1,1,4.5),glm::vec3(0, 90.0f, 0));
	WallManager::addWall(glm::vec3(-4.75f,-2.0f,-10.5f), glm::vec3(1,1,4.5),glm::vec3(0, 90.0f, 0));
	WallManager::addWall(glm::vec3(4.75f,-2.0f,-10.5f), glm::vec3(1,1,4.5),glm::vec3(0, 90.0f, 0));
	WallManager::addWall(glm::vec3(-6.75f,-2.0f,-9.75f), glm::vec3(1,1,4.5),glm::vec3(0, -15.0f, 0));
	WallManager::addWall(glm::vec3(-7.0f,-2.0f,-9.5f), glm::vec3(1,1,4.5),glm::vec3(0, -45.0f, 0));
	WallManager::addWall(glm::vec3(6.75f,-2.0f,-9.75f), glm::vec3(1,1,4.5),glm::vec3(0, 15.0f, 0));
	WallManager::addWall(glm::vec3(7.0f,-2.0f,-9.5f), glm::vec3(1,1,4.5),glm::vec3(0, 45.0f, 0));
	WallManager::addWall(glm::vec3(-6.75f,-2.0f,9.75f), glm::vec3(1,1,4.5),glm::vec3(0, 195.0f, 0));
	WallManager::addWall(glm::vec3(-7.0f,-2.0f,9.5f), glm::vec3(1,1,4.5),glm::vec3(0, 225.0f, 0));
	WallManager::addWall(glm::vec3(6.75f,-2.0f,9.75f), glm::vec3(1,1,4.5),glm::vec3(0, 345.0f, 0));
	WallManager::addWall(glm::vec3(7.0f,-2.0f,9.5f), glm::vec3(1,1,4.5),glm::vec3(0, 315.0f, 0));
}

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	QApplication app(argc, argv);
	Engine::Init(update);
	LightManager::initialize();
	LightManager::addLight(glm::vec3(-2.5f, 4.5f, .5f), glm::vec3(1,1,1), .5f);
	WallManager::initialize(glm::vec3(0,-2.1f,0), glm::vec3(5.2f,4.5f,4.0f));
	puck.initialize(glm::vec3(0,-2.0f,0));
	createWalls();
	PlayerManager::createPlayer(glm::vec3(0,-1.0f,9.0f), glm::vec3(), glm::vec3(1.0f,1.0f,1.0f));
	PlayerManager::createPlayer(glm::vec3(0,-1.0f,-9.0f), glm::vec3(0,180.0f,0), glm::vec3(1.0f,1.0f,1.0f));
	t.startTimer();
	app.exec();
	shutdown();
	return 0;
}