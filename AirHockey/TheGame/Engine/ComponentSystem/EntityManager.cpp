#include <ComponentSystem\EntityManager.h>
#include <ComponentSystem\Component.h>
#include <DebugTools\DebugMemory.h>
#include <Qt\qdebug.h>
#include "ComponentSystem\State.h"

QList<EntityManager::Entity*> entities;

void EntityManager::Entity::addComponent(Component* c)
{
	components.push_back(c);
}

Component* EntityManager::Entity::findComponent(QString name)
{
	Component* comp = nullptr;
	for(int i=0; i<components.size() && comp == nullptr; i++)
	{
		comp = (components[i]->name == name)?components[i]:nullptr;
	}
	return comp;
}

EntityManager::Entity::~Entity()
{
	EntityManager::removeEntity(this);
	shutdown();
}

void EntityManager::Entity::shutdown()
{
	for(int i=0; i<components.size(); i)
	{
		if(components[i]->canBeDeleted)
		{
			delete components[i];
			components.erase(components.begin()+i);
		}
		else
		{
			i++;
		}
	}
}

void EntityManager::Entity::update()
{
	for(int i=0; i<components.size(); i++)
	{
		components[i]->update();
	}
}

void EntityManager::addEntity(Entity* e)
{
	entities.push_back(e);
}

void EntityManager::removeEntity(Entity* e)
{
	entities.removeOne(e);
}

EntityManager::Entity* EntityManager::findEntity(Entity* e)
{
	Entity* ret = nullptr;
	for(int i=0; i<entities.size() && !ret; i++)
	{
		ret = (entities[i] == e)?entities[i]:nullptr;
	}
	return ret;
}

bool EntityManager::entityHasComponent(Entity* e, Component* c)
{
	return e->components.contains(c);
}

void EntityManager::update()
{
	for(int i=0; i<entities.size(); i++)
	{
		entities[i]->update();
	}
}

void EntityManager::shutdown()
{
	for(int i=0; i<entities.size(); i++)
	{
		entities[i]->shutdown();
	}
}
