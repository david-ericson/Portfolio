#include <ComponentSystem\EntityManager.h>

#pragma once
class Component
{
public:
	EntityManager::Entity* parent;
	bool canBeDeleted;
	QString name;
	virtual void update() = 0;
	virtual ~Component(){};
};

