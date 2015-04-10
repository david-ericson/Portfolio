#include "Component.h"
#include "GeneralGLWindow.h"

#pragma once
class TextComponent : public Component
{
public:
	enum Follow
	{
		followInt,
		followFloat,
	};
	glm::vec3 penColor;
	GeneralGLWindow::TextureInfo* texture;
	int numSignifDigits;
	float since;
	float reset;
	float numLastUpdate;
	bool setupOnce;
	void* following;
	Follow followMode;
	ENGINE_SHARED TextComponent(EntityManager::Entity* e, float resetTime, GeneralGLWindow::TextureInfo* text, void* numberToFollow, Follow mode = followInt, int signifDigits = 1, glm::vec3 color = glm::vec3(255,0,0));
	void update();
	void floatUpdate();
	void intUpdate();
	~TextComponent(void);
};

