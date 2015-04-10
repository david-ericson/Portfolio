#pragma once
#include <vector>
#include "movingText.h"
using std::vector;

class movingTextManager
{
	vector<movingText*> myText;
public:
	void addText(float thickness, Core::RGB color, const char* text, float size, float gap, float lifetime, Vector2D startPosition);
	void deleteText(unsigned int victim);
	void drawText(Core::Graphics& graphics);
	void updateText(float dt);
	void resetText();
};

