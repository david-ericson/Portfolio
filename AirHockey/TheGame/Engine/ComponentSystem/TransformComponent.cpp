#include <ComponentSystem\TransformComponent.h>
#include <glm\gtx\transform.hpp>
#include "DebugTools\DebugMemory.h"

TransformComponent::TransformComponent()
{
	canBeDeleted = false;
	name = "TransformComponent";
	scale = glm::vec3(1.0f,1.0f,1.0f);
}

void TransformComponent::update()
{
	rotateMat = glm::rotate(rotate.x, glm::vec3(1,0,0))*glm::rotate(rotate.y, glm::vec3(0,1.0f,0))*glm::rotate(rotate.z, glm::vec3(0,0,1.0f));
}

TransformComponent::~TransformComponent(){}
