#include <ComponentSystem\Component.h>
#include <GeneralGLWindow.h>
#include <ComponentSystem\TransformComponent.h>

#pragma once
class RenderableComponent : public Component
{
public:
	bool isVisible;
	GeneralGLWindow::RenderableInfo* graphic;
	TransformComponent transform;
	ENGINE_SHARED RenderableComponent(EntityManager::Entity* e, char* fileName, char* vertexShader = "AlphaMapVertexShader.glsl", char* fragShader = "TextureFragmentShader.glsl", char* texture = "white.png", 
		char* alphaMap = nullptr, char* normalMap = nullptr, char* aoMap = nullptr, glm::mat4 transform = glm::mat4());
	ENGINE_SHARED void update();
	ENGINE_SHARED ~RenderableComponent();
};

