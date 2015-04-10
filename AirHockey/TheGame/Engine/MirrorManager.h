#include <Camera.h>
#include <glm\glm.hpp>
#include <ExportHeader.h>
#include <GeneralGLWindow.h>
#pragma once

static int currentMirror = 0;

class MirrorManager
{
public:	
	
	static struct Mirror
	{
		Camera* camera;
		float angle;
		glm::vec3 ambColor;
		glm::vec3 normal;
		glm::vec3 position;
		GeneralGLWindow::RenderableInfo* graphic;
		bool visible;
		void update(float dt);
	};

	ENGINE_SHARED static void initialize();
	ENGINE_SHARED static void createNewPassForMirror(int mirror);
	ENGINE_SHARED static void addMirror(glm::vec3 position, float yAngle, float xAngle);
	ENGINE_SHARED static void update(float dt);
};

