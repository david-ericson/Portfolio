#include "ComponentSystem\PhysicsComponent.h"
#include "ComponentSystem\RenderableComponent.h"

struct Player;

#pragma once
class Puck : public EntityManager::Entity
{
public:
	PhysicsComponent* physics;
	RenderableComponent* render;
	Player* server;
	void initialize(glm::vec3 start);
	void update();
	void checkCollision(Player* player);
	~Puck();
};

