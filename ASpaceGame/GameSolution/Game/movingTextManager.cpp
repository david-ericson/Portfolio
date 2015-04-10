#include "movingTextManager.h"
#include "DebugMemory.h"
	
void movingTextManager::addText(float thickness, Core::RGB color, const char* text, float size, float gap, float lifetime, Vector2D startPosition)
{
	const char* meText = text;
	meText;
	movingText* newText = new movingText(thickness, color, text, size, gap, lifetime, startPosition);
	myText.push_back (newText);
}

void movingTextManager::deleteText(unsigned int victim)
{
	delete myText[victim];
	myText.erase(myText.begin() + victim);
}

void movingTextManager::drawText(Core::Graphics& graphics)
{
	for(unsigned int i=0; i<myText.size(); i++)
	{
		myText[i]->drawText(graphics);
	}
}

void movingTextManager::updateText(float dt)
{
	for(unsigned int i=0; i<myText.size(); i++)
	{
		myText[i]->updateText(dt);
		if(myText[i]->lifetimeIsOver())
		{
			deleteText(i);
		}
	}
}

void movingTextManager::resetText()
{
	for(unsigned int i=0; i<myText.size(); i)
	{
		deleteText(0);
	}
}