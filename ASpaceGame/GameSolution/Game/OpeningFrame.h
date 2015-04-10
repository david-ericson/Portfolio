#include "Core.h"
#include "Vector2D.h"
#include "Button.h"
#include "Backdrop.h"
#include "RandomColors.h"

extern Backdrop myBackground;
static Button titleButton(RGB(0,0,0), Vector2D(675.0f, 385.0f));
static Button startButton(RGB(214, 96, 50), Vector2D(875.0f, 540.0f));

class OpeningFrame
{
	RandomColors randColor;
	float fadeTiming;
	bool currentFrame, fadingIn;
public:
	OpeningFrame();
	void DrawFrame(Core::Graphics& graphics);
	void UpdateFrame(Vector2D mouse, float dt);
	void setCurrentFrame(bool value);
	bool getIsCurrentFrame();
};