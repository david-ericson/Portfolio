#include <Camera.h>
#include <glm\gtx\transform.hpp>
#include <DebugTools\DebugMemory.h>

Camera::Camera()
{
	viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
}
void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if(glm::length(mouseDelta) > 50.0f)
	{
		oldMousePosition = newMousePosition;
	}
	else
	{
		strafeDirection = glm::cross(viewDirection, UP);
		const float ROTATE_SPEED = .5f;
		viewDirection = glm::mat3(
			glm::rotate(-mouseDelta.x * ROTATE_SPEED, UP)*
			glm::rotate(-mouseDelta.y * ROTATE_SPEED, strafeDirection))*viewDirection;

		oldMousePosition = newMousePosition;
	}
}
glm::vec3 Camera::getPosition()
{
	return position;
}
glm::vec3 Camera::getViewDirection()
{
	return viewDirection;
}
void Camera::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Camera::setViewDirection(glm::vec3 newDirection)
{
	viewDirection = newDirection;
}

void Camera::moveForward()
{
	position += MOVEMENT_SPEED * viewDirection;
}
void Camera::moveBackward()
{
	position += -MOVEMENT_SPEED * viewDirection;
}
void Camera::strafeLeft()
{
	
	position += -MOVEMENT_SPEED*strafeDirection;
}
void Camera::strafeRight()
{
	position += MOVEMENT_SPEED*strafeDirection;
}
void Camera::moveUp()
{
	position += MOVEMENT_SPEED * UP;
}
void Camera::moveDown()
{
	position += -MOVEMENT_SPEED * UP;
}
glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}


