#pragma once
#include <glm\glm.hpp>
#include <ExportHeader.h>

static const float MOVEMENT_SPEED = .1f;
const glm::vec3 UP(0,1.0f,0);

class Camera
{
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec2 oldMousePosition;
	glm::vec3 strafeDirection;
public:
	ENGINE_SHARED Camera(void);
	void mouseUpdate(const glm::vec2& newMousePosition);
	ENGINE_SHARED glm::mat4 getWorldToViewMatrix() const;
	ENGINE_SHARED glm::vec3 getPosition();
	ENGINE_SHARED glm::vec3 getViewDirection();
	ENGINE_SHARED void setPosition(glm::vec3 newPosition);
	ENGINE_SHARED void setViewDirection(glm::vec3 newDirection);
	void moveForward();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void moveUp();
	void moveDown();
};

