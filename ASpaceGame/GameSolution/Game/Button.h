#include "Core.h"
#include "Vector2D.h"
#include "GameplayFrame.h"

extern GameplayFrame gameFrame;

class Button
{
	Core::RGB myColor, originalColor;
	Vector2D letPosition;
	float letSize, letGap, newSize;
	int currentLet;
public:
	Vector2D position;
	float size;
	const char* text;
	bool mouseOver;
	Button(Core::RGB color, Vector2D startPosition);
	void DrawButton(Core::Graphics& graphics, Core::RGB colorText, float thickness);
	void DrawButtonText(Core::Graphics& graphics, Core::RGB colorText, float thickness);
	void DrawHorizontalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition);
	void DrawVerticalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition);
	void DrawDiagonalBar(Core::Graphics& graphics, float thickness, Vector2D startPosition, Vector2D endPosition);
	void UpdateButton(Vector2D mouse);
};