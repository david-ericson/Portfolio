#include <Engine.h>
#include <BaseWidg.h>
#include <graphics.h>
#include <DebugTools\DebugMenus.h>
#include <ComponentSystem\EntityManager.h>

namespace Engine
{
	void (*update)(void);
	BaseWidg *theWidget;

	void Init(void(updateMethod)(void))
	{
		Engine::update = updateMethod;
		theWidget = new BaseWidg;
		theWidget->widget = new GeneralGLWindow();
		DebugMenus::initialize(theWidget->widget);
	}

	void callUpdate()
	{
		EntityManager::update();
		update();
	}

	bool sampleFunctionThatReturnsTrue()
	{
		return true;
	}

	void shutdown()
	{
		delete theWidget;
	}
}
