#include "EntityManager.h"
#include "InputComponent.h"
#include "RenderableComponent.h"

#pragma once
class Fish : public EntityManager::Entity
{
public:
	glm::vec3 forward;
	glm::vec3 currForward;
	RenderableComponent* graphic;
	InputComponent* input;
	void initialize();
	void update();
	void moveForward();
	void moveBackward();
};

