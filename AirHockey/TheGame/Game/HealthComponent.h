#include "ComponentSystem\RenderableComponent.h"




#pragma once
class HealthComponent : public Component
{
	struct HealthRender
	{
		RenderableComponent* render;
		glm::vec3 relation;
	};
	int* hp;
	char* fileName;
	glm::vec3 scale;
	glm::vec4 color;
	float specExp;
	int hpLastFrame;
	float currRotation;
	QList<HealthRender*> hearts;
float gap;
public:
	
	RenderableComponent* originalPlayer;
	HealthComponent(EntityManager::Entity* parent, char* file, int* hp, RenderableComponent* player, glm::vec4 theColor = glm::vec4(1.0f,0,0, 1.0f));
	void update();
	~HealthComponent();
};

