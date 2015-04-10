#include "WallManager.h"
#include "LightManager.h"
#include <Qt\qdebug.h>
#include <Qt\qlist.h>
#include "Wall.h"
#include "Puck.h"

QList<Wall*> walls;
WallManager::Table* table;
float tableSpec = 20.0f;
glm::vec3 tableAmb(.1f,.1f,.1f);

WallManager::Table::Table(glm::vec3 pos, glm::vec3 scale)
{
	EntityManager::addEntity(this);
	render = new RenderableComponent(this, "AirHockeyTable.bin", "NormalMapVertexShader.glsl", "NormalMapFragmentShader.glsl", "AirHockeyTable.png");
	GeneralGLWindow::addLightingUniforms(render, LightManager::getLight(0), &tableSpec, &tableAmb);
	render->transform.position = pos;
	render->transform.scale = scale;
	render->graphic->addFramebufferID(0);
	render->graphic->addFramebufferID(1);
	addComponent(render);
}

void WallManager::initialize(glm::vec3 pos, glm::vec3 scale)
{
	table = new Table(pos, scale);
}

void WallManager::addWall(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot)
{
	walls.push_back(new Wall(pos, scale, rot));
}

void WallManager::checkCollisions(Puck* puck)
{
	for(int i=0; i<walls.size(); i++)
	{
		if(walls[i]->isColliding(puck))
		{
			resolveCollision(walls[i], puck);
		}
	}
}

void WallManager::resolveCollision(Wall* wall, Puck* puck)
{
	glm::vec3 normal = (glm::dot(wall->normal, puck->physics->velocity) >= 0) ? -1.0f*wall->normal:wall->normal;
	puck->physics->velocity = puck->physics->velocity - 2*glm::dot(puck->physics->velocity, normal)*normal;
	puck->physics->update();
}


void WallManager::shutdown()
{
	while(walls.size() > 0)
	{
		delete walls.first();
		walls.removeFirst();
	}
	delete table;
}
