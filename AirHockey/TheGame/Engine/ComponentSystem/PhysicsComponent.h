#include "ComponentSystem\Component.h"
#include <glm\glm.hpp>

#pragma once
class PhysicsComponent : public Component
{
public:
	glm::vec3* pos;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float minVelocity;
	float maxVelocity;
	float mass;
	bool isDecellerating;

	ENGINE_SHARED PhysicsComponent(EntityManager::Entity* e, glm::vec3* ownerPos);
	void update();
	void addForce(glm::vec3 force);
	ENGINE_SHARED void setAcc(glm::vec3 acclr, float maxVel, bool decellerating = false);
	~PhysicsComponent();
};

