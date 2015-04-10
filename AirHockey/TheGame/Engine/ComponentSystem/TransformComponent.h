#include <glm\glm.hpp>
#include <ComponentSystem\Component.h>

#pragma once
class TransformComponent : public Component
{
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotate;
	glm::vec3 originalBounds;
	glm::mat4 rotateMat;
	TransformComponent();
	ENGINE_SHARED void update();
	~TransformComponent();

};

