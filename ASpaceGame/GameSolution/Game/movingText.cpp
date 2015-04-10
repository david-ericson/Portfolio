#include "movingText.h"

movingText::movingText(float myThickness, Core::RGB color, const char* myText, float letter_size, float letter_gap, float lifetime, Vector2D startPosition)
{
	position = startPosition;
	velocity = Vector2D(0, -215.0f);
	thickness = myThickness;
	textColor = color;
	size = letter_size;
	gap = letter_gap;
	text = myText;
	life = lifetime;
}

void movingText::drawText(Core::Graphics& graphics)
{
	if(life > 0)
	{
		myText.drawText(graphics, thickness, textColor, text, size, gap, 0, position);
	}
}

void movingText::updateText(float dt)
{
	if(life > 0)
	{
		life -= dt;
	}
	position = position + (velocity *dt);
}

bool movingText::lifetimeIsOver()
{
	return (life<=0);
}
