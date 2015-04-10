#include <ExportHeader.h>
#include <Qt\qstring.h>
#include <Qt\qlist.h>
#include <vector>
using std::vector;

class Component;
class State;

#pragma once
class EntityManager
{
public:
	struct Entity
	{
		State* currState;
		QList<Component*> components;
		ENGINE_SHARED void addComponent(Component* c);
		Component* findComponent(QString name);
		void update();
		ENGINE_SHARED void shutdown();
		ENGINE_SHARED ~Entity();
	};
	ENGINE_SHARED static void addEntity(Entity* e);
	ENGINE_SHARED static void removeEntity(Entity* e);
	ENGINE_SHARED static Entity* findEntity(Entity* e);
	ENGINE_SHARED static bool entityHasComponent(Entity* e, Component* c);
	static void update();
	ENGINE_SHARED static void shutdown();
	~EntityManager(void);
};

