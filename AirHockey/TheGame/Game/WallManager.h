#include "ComponentSystem\RenderableComponent.h"
#include <glm\glm.hpp>

class Wall;
class Puck;

#pragma once
class WallManager 
{
public:
	struct Table: public EntityManager::Entity
	{
		RenderableComponent* render;
		Table(glm::vec3 pos, glm::vec3 scale);
	};
	static void initialize(glm::vec3 pos, glm::vec3 scale);
	static void addWall(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);
	static void checkCollisions(Puck* puck);
	static void resolveCollision(Wall* wall, Puck* puck);
	static void shutdown();
};

