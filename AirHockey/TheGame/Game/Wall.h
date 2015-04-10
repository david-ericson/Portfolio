#include "ComponentSystem\RenderableComponent.h"

class Puck;

#pragma once 
class Wall : public EntityManager::Entity
{
	RenderableComponent* render;
public:
	glm::vec3 normal;
	float widthToAdd;
	Wall(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);
	bool isColliding(Puck* puck);
	~Wall();
};

