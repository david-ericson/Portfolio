#include "PhysicsComponent.h"
#include "DebugTools\Timer.h"
#include <Qt\qdebug.h>

PhysicsComponent::PhysicsComponent(EntityManager::Entity* e, glm::vec3* ownerPos)
{
	parent = e;
	pos = ownerPos;
	maxVelocity = 10000;
	name = "PhysicsComponent";
	isDecellerating = false;
	mass = 1.0f;
	minVelocity = 0;
}

void PhysicsComponent::update()
{
	velocity += acceleration*Timer::dt();
	velocity = (glm::length(velocity) > maxVelocity)?glm::normalize(velocity)*maxVelocity:velocity;
	velocity = (glm::length(velocity) < minVelocity)?glm::normalize(velocity)*minVelocity:velocity;
	if(isDecellerating && glm::dot(velocity, acceleration) > 0)
	{
		velocity = glm::vec3();
		acceleration = glm::vec3();
		isDecellerating = false;
	}
	*pos += velocity*Timer::dt();
}

void PhysicsComponent::addForce(glm::vec3 force)
{
	velocity += force*Timer::dt();
}

void PhysicsComponent::setAcc(glm::vec3 acclr, float maxVel, bool decellerating)
{
	acceleration = acclr;
	maxVelocity = maxVel;
	isDecellerating = decellerating;
	if(isDecellerating && glm::length(velocity)>0)
	{
		acceleration = (-1.0f*glm::normalize(velocity))*(float)glm::length(acclr);
	}
}

PhysicsComponent::~PhysicsComponent()
{
}
