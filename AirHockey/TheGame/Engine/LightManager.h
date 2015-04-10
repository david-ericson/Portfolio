#include <glm\glm.hpp>
#include <ExportHeader.h>
#include <Light.h>

#pragma once
class LightManager
{
public:
	enum menuType
	{
		pos,
		diffColor,
		visibility,
		scalar,
	};

	ENGINE_SHARED static void initialize();
	ENGINE_SHARED static int addLight(glm::vec3 position, glm::vec3 color, float scale);
	ENGINE_SHARED static Light* getLight(int index);
	ENGINE_SHARED static int getFirstLight();
	ENGINE_SHARED static void addDebugValueToLight(int index, menuType mt, char* tabName, float min=0, float max=0, int granuality=0);
	ENGINE_SHARED static void update(float dt);
	ENGINE_SHARED static void shutdown();
};

