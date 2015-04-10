#include "ComponentSystem\EntityManager.h"

#pragma once
class State
{
public:
	EntityManager::Entity* parent;
	QString name;
	State* onComplete;
	virtual void update() = 0;
	virtual ~State(){};
};

