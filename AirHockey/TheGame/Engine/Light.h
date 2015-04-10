#include "glm\glm.hpp"
#include "GeneralGLWindow.h"

#pragma once
class Light
{
	GeneralGLWindow::RenderableInfo* graphic;
	
	float scale;
	
	bool visible;
	
public:
	glm::vec3 position;
	glm::vec3 diffuseColor;
	int index;
	enum menuType
	{
		pos,
		diffColor,
		visibility,
		scalar,
	};

	ENGINE_SHARED Light(glm::vec3 myPosition, glm::vec3 myColor, float myScale = 1.0f);
	ENGINE_SHARED void addDebugMenu(menuType type, float min, float max, int granuality, char* tabName);
	ENGINE_SHARED void update(float dt);
};

