#include "OpeningFrame.h"

OpeningFrame::OpeningFrame()
{
	startButton.text = "START";
	titleButton.text = "A SPACE GAME";
	fadeTiming = 2.0f;
	fadingIn = true;
	currentFrame = true;
}

void OpeningFrame::DrawFrame(Core::Graphics& graphics)
{
	myBackground.DrawBackdrop(graphics);
	Core::RGB textColor = randColor.brightness(RGB(255,255,255), 1.0f - (fadeTiming / 2.0f));
	titleButton.DrawButton(graphics, textColor, 5.0f);
	startButton.DrawButton(graphics,RGB(255,255,255), 3.0f);
}

void OpeningFrame::UpdateFrame(Vector2D mouse, float dt)
{
	if(fadeTiming > 0 && fadingIn)
	{
		fadeTiming -= dt;
		if(fadeTiming <= 0)
		{
			fadingIn = false;
		}
	}
	else if(fadeTiming < 2.0f && !fadingIn)
	{
		fadeTiming += dt;
		if(fadeTiming >= 2.0f)
		{
			fadingIn = true;
		}
	}
	startButton.UpdateButton(mouse);
}

void OpeningFrame::setCurrentFrame(bool value)
{
	currentFrame = value;
}

bool OpeningFrame::getIsCurrentFrame()
{
	return currentFrame;
}