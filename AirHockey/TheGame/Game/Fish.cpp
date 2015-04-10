#include "Fish.h"
#include "DebugMenus.h"
#include "DebugMemory.h"
#include "Timer.h"

void Fish::initialize()
{
	EntityManager::addEntity(this);
	graphic = new RenderableComponent(this, "Fish.bin");
	input = new InputComponent(this);

	DebugMenus::addTab("Fish w/ Components");
	DebugMenus::slide("Rotation (y)", 0, 360, 360, 0, "Fish w/ components", &graphic->transform.rotate.y);
	forward = glm::vec3(0,0,-2.0f);
	currForward = forward;
	input->addInput(38, fastdelegate::MakeDelegate(this, &Fish::moveForward));
	input->addInput(40, fastdelegate::MakeDelegate(this, &Fish::moveBackward));

	addComponent(graphic);
	addComponent(input);

}

void Fish::moveForward()
{
	graphic->transform.position += currForward*Timer::dt();
}

void Fish::moveBackward()
{
	graphic->transform.position -= currForward*Timer::dt();
}

void Fish::update()
{
	glm::vec3 rotation = graphic->transform.rotate;
	currForward = glm::vec3(glm::vec4(forward,0) * (glm::rotate(-rotation.x, glm::vec3(1,0,0)) * glm::rotate(-rotation.y, glm::vec3(0,1,0))* glm::rotate(-rotation.z, glm::vec3(0,0,1))));
}

