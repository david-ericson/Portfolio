#include <ComponentSystem\RenderableComponent.h>
#include <glm\gtx\transform.hpp>
#include <Qt\qdebug.h>

RenderableComponent::RenderableComponent(EntityManager::Entity* e, char* fileName, char* vertexShader, char* fragShader, char* texture, char* alphaMap, char* normalMap, char* aoMap, glm::mat4 mTransform)
{
	graphic = nullptr;
	graphic = GeneralGLWindow::readBinaryFile(fileName, vertexShader, fragShader, texture, alphaMap, normalMap, aoMap, mTransform);
	if(graphic == nullptr)
	{
		QString file = fileName;
		file = file.replace(".bin", ".obj");
		GeneralGLWindow::createOBJ(file.toUtf8().data(), true);
		graphic = GeneralGLWindow::readBinaryFile(fileName, vertexShader, fragShader, texture, alphaMap, normalMap, aoMap, mTransform);
	}
	parent = e;
	transform.originalBounds = graphic->bounds;
	transform.position = glm::vec3(mTransform[3][0],mTransform[3][1],mTransform[3][2]);
	graphic->setVisibility(EntityManager::findEntity(parent));
	name = "RenderableComponent";
	parent->addComponent(&transform);
	isVisible = true;
	canBeDeleted = true;
	update();
}

void RenderableComponent::update()
{
	graphic->setTransform(glm::translate(transform.position) * transform.rotateMat* glm::scale(transform.scale));
	graphic->bounds = glm::vec3(transform.originalBounds.x*transform.scale.x, transform.originalBounds.y * transform.scale.y,transform.originalBounds.z*transform.scale.z);
	graphic->bounds = glm::vec3(glm::rotate(transform.rotate.x, glm::vec3(1.0f,0,0)) * glm::rotate(transform.rotate.y, glm::vec3(0,1.0f,0))  * 
		glm::rotate(transform.rotate.z, glm::vec3(0,0,1.0f)) * glm::vec4(graphic->bounds,1.0f));
	graphic->bounds = glm::vec3(abs(graphic->bounds.x), abs(graphic->bounds.y), abs(graphic->bounds.z));
	graphic->setVisibility(EntityManager::findEntity(parent) && isVisible);
}

RenderableComponent::~RenderableComponent()
{
	graphic->setVisibility(false);
	isVisible = false;
}
