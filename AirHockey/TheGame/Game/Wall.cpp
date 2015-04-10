#include <glm\gtx\transform.hpp>
#include "Wall.h"
#include "LightManager.h"
#include "Puck.h"
#include "DebugTools\Timer.h"
#include <Qt\qdebug.h>

float wallSpec = 150.0f;
glm::vec3 wallAmbColor(.1f,.1f,.1f);

Wall::Wall(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot)
{
	EntityManager::addEntity(this);
	render = new RenderableComponent(this, "Cube.bin", "NormalMapVertexShader.glsl", "NormalMapFragmentShader.glsl", "white.png");
	GeneralGLWindow::addLightingUniforms(render, LightManager::getLight(0), &wallSpec, &wallAmbColor);
	render->transform.position = pos;
	render->transform.rotate = rot;
	render->transform.scale = scale;
	normal = glm::vec3(1.0f,0,0);
	normal = glm::vec3(glm::rotate(rot.x, glm::vec3(1.0f,0,0))*glm::rotate(rot.y, glm::vec3(0,1.0f,0))*glm::rotate(rot.z, glm::vec3(0,0,1.0f))*glm::vec4(normal,0));
	widthToAdd = glm::length(normal*(scale.x/2));
	addComponent(render);
	render->isVisible = false;
}

bool Wall::isColliding(Puck* puck)
{
	glm::vec3 posNextFrame = puck->render->transform.position + puck->physics->velocity*Timer::dt();
	glm::vec3 normalToCheck = (glm::dot(puck->physics->velocity, normal) <= 0)?normal:-1.0f*normal;
	glm::vec3 relative = posNextFrame-render->transform.position;
	float testValue = glm::dot(relative, normalToCheck);
	float widthValue = glm::abs(glm::dot(relative, glm::vec3(-normalToCheck.z, 0, normalToCheck.x)));
	bool letMeSee = (testValue <= puck->render->graphic->bounds.x/2 + widthToAdd && testValue > 0 && widthValue < puck->render->graphic->bounds.x/2+glm::abs(glm::dot(render->transform.scale, glm::vec3(-normalToCheck.z,0,normalToCheck.x))));
	return letMeSee;
}

Wall::~Wall()
{
}
