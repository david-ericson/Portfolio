#include "TextComponent.h"
#include "DebugTools\Timer.h"
#include "RenderableComponent.h"

TextComponent::TextComponent(EntityManager::Entity* e, float resetTime, GeneralGLWindow::TextureInfo* tex, void* numberToFollow, Follow mode, int signifDigits, glm::vec3 color)
{
	name = "TextComponent";
	reset = resetTime;
	since = reset;
	texture = tex;
	numLastUpdate = -9999.0f;
	following = numberToFollow;
	parent = e;
	followMode = mode;
	numSignifDigits = signifDigits;
	QString num;
	setupOnce = false;
	if(following)
	{
		if(followMode == followFloat)
		{
			num = QString::number(*reinterpret_cast<float*>(numberToFollow));
		}
		else
		{
			num = QString::number(*reinterpret_cast<int*>(following));
		}
	}
	//GeneralGLWindow::setupTextTexture(num, texture);
	penColor = color;
	update();
}

void TextComponent::update()
{
	if(since >= reset && following)
	{
		since = 0;
		if(followMode == followFloat)
		{
			floatUpdate();
		}
		else if(followMode == followInt)
		{
			intUpdate();
		}
	}
	else
	{
		since += Timer::dt();
	}
}

void TextComponent::floatUpdate()
{
	float value = *reinterpret_cast<float*>(following);
	if(numLastUpdate != value)
	{
		float devisor = pow(10,numSignifDigits);
		float actualNum = (int)(value*devisor);
		if(numSignifDigits == 0)
		{
			actualNum = (int)(ceil(value*devisor));
		}
		float actualActualNum = ceil((actualNum)/devisor);
		QString num = QString::number(actualActualNum);
		if(!setupOnce)
		{
			RenderableComponent* render = (RenderableComponent*)(parent->findComponent("RenderableComponent"));
			render->graphic->setTexture(GeneralGLWindow::setupTextTexture(num, nullptr, penColor));
			texture = render->graphic->getTexture();
			setupOnce = true;
		}
		else
		{
			GeneralGLWindow::setupTextTexture(num, texture, penColor);
		}
		numLastUpdate = value;
		
	}
}

void TextComponent::intUpdate()
{
	int value = *reinterpret_cast<int*>(following);
	if(numLastUpdate != value)
	{
		QString num = QString::number(value);
		if(!setupOnce)
		{
			RenderableComponent* render = (RenderableComponent*)(parent->findComponent("RenderableComponent"));
			render->graphic->setTexture(GeneralGLWindow::setupTextTexture(num, nullptr, penColor));
			texture = render->graphic->getTexture();
			setupOnce = true;
		}
		else
		{
			GeneralGLWindow::setupTextTexture(num, texture, penColor);
		}
		
		numLastUpdate = value;
	}
}

TextComponent::~TextComponent(){}
