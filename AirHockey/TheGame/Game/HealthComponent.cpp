#include "HealthComponent.h"
#include <Qt\qlist.h>
#include <Qt\qdebug.h>
#include "DebugTools\DebugMemory.h"
#include "DebugTools\Profile.h"
#include "LightManager.h"

float yGap = .25f;


HealthComponent::HealthComponent(EntityManager::Entity* e, char* file, int* health, RenderableComponent* player, glm::vec4 theColor)
{
	fileName = file;
	parent = e;
	originalPlayer = player;
	hp = health;
	hpLastFrame = 0;
	color = theColor;
	specExp = 1000.0f;
	currRotation = 0;
	scale = glm::vec3(.1f, .1f, .1f);
	canBeDeleted = true;
	glm::vec3 playerPos = player->transform.position;
	glm::vec3 playerBounds = player->graphic->bounds;
	/*for(int i=0; i<*health; i++)
	{
		HealthRender* heart = new HealthRender;
		heart->render = new RenderableComponent(parent, fileName);
		parent->addComponent(heart->render);
		heart->render->transform.scale = scale;
		heart->render->update();
		gap = heart->render->graphic->bounds.x/2;
		heart->render->isVisible = true;
		heart->relation = glm::vec3(playerPos.x-playerBounds.x/2+heart->render->graphic->bounds.x/2+i*(heart->render->graphic->bounds.x+gap), playerPos.y+playerBounds.y/2+yGap, playerPos.z) - playerPos;
		hearts.push_back(heart);
	}*/
}

void HealthComponent::update()
{
	if(EntityManager::entityHasComponent(parent, this))
	{
		if(hpLastFrame != *hp)
		{
			if(hpLastFrame > *hp)
			{
				hearts[hearts.size()-1]->render->isVisible = false;
				delete hearts[hearts.size()-1];
				hearts.removeLast();
			}
			else
			{
				glm::vec3 playerPos = originalPlayer->transform.position;
				glm::vec3 playerBounds = originalPlayer->graphic->bounds;
				while(hpLastFrame < *hp)
				{
					int i = hearts.size();
					HealthRender* heart = new HealthRender;
					heart->render = new RenderableComponent(parent, fileName, "NormalMapVertexShader.glsl", "NormalMapFragmentShader.glsl");
					GeneralGLWindow::addLightingUniforms(heart->render, LightManager::getLight(0), &specExp, &scale, &color);
					parent->addComponent(heart->render);
					heart->render->transform.scale = scale;
					//heart->render->update();
					glm::vec3 graphicBounds = heart->render->graphic->bounds * scale;
					gap = graphicBounds.z;
					heart->render->isVisible = true;
					heart->relation = glm::vec3(playerPos.x-playerBounds.x/2+graphicBounds.x/2+i*(graphicBounds.x+gap), playerPos.y+playerBounds.y/2+yGap, playerPos.z) - playerPos;
					hearts.push_back(heart);
					hpLastFrame++;
				}
			}
		}
		for(int i=0; i<hearts.size(); i++)
		{
			hearts[i]->render->transform.position = originalPlayer->transform.position + hearts[i]->relation;
			hearts[i]->render->transform.rotate.y = currRotation; 
			hearts[i]->render->isVisible = originalPlayer->isVisible;
		}
		currRotation += 180*Timer::dt();
		currRotation -= (currRotation > 360)?360:0;
		hpLastFrame = *hp;
	}
}

HealthComponent::~HealthComponent(void)
{
	for(int i=0; i<hearts.size(); i)
	{
		delete hearts[i];
		hearts.removeFirst();
	}
}
