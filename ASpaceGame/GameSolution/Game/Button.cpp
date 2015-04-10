#include "Button.h"


Button::Button(Core::RGB color, Vector2D startPosition)
{
	position = startPosition;
	myColor = color;
	originalColor = color;
	size = 150.0f;
	letSize = 15.0f;
	letGap = 5.0f;
}

void Button::DrawButton(Core::Graphics& graphics, Core::RGB textColor, float thickness)
{
	graphics.SetColor(myColor);
	letSize = thickness * 8;
	newSize = size * thickness/2-letSize;
	letPosition=Vector2D(position.x + 3*(newSize/20), position.y + newSize/10);
	for(int i=0; i<newSize; i++)
	{
		Vector2D start(position.x, position.y + i/3);
		Vector2D end(position.x + newSize, position.y + i/3);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
	DrawButtonText(graphics, textColor, thickness);
}

void Button::DrawButtonText(Core::Graphics& graphics, Core::RGB textColor, float thickness)
{
	graphics.SetColor(textColor);
	currentLet =  0;
	for(unsigned int i=0; i<strlen(text); i++)
	{
		switch(text[i])
		{
		case('S'):
			DrawHorizontalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y));
			DrawVerticalBar(graphics, thickness, (letSize-3*thickness)/2, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y + thickness));
			DrawHorizontalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y+thickness+((letSize-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(letSize-3*thickness)/2, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+(letSize-thickness), letPosition.y + thickness*2+((letSize-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y+2*thickness + 2*((letSize-3*thickness)/2)));
			currentLet++;
			break;
		case('A'):
			DrawVerticalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y));
			DrawHorizontalBar(graphics, thickness, letSize - thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness, letPosition.y));
			DrawVerticalBar(graphics, thickness, letSize-thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness + (letSize-thickness*2), letPosition.y + thickness));
			DrawHorizontalBar(graphics, thickness, letSize-thickness*2, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness, letPosition.y+thickness+(letSize-thickness*2)/3));
			currentLet++;
			break;
		case('T'):
			DrawHorizontalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet,letPosition.y));
			DrawVerticalBar(graphics, thickness, letSize-thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+(letSize-thickness)/2,letPosition.y+thickness));
			currentLet++;
			break;
		case('R'):
			DrawVerticalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet,letPosition.y));
			DrawHorizontalBar(graphics, thickness, letSize-2*thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness,letPosition.y));
			DrawHorizontalBar(graphics, thickness, letSize-2*thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness,letPosition.y+(letSize-2*thickness)/3+thickness));
			DrawVerticalBar(graphics, thickness, (letSize-2*thickness)/3, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+letSize-thickness,letPosition.y+thickness));
			DrawVerticalBar(graphics, thickness, 2*(letSize-2*thickness)/3, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+letSize-thickness,letPosition.y+(letSize-2*thickness)/3+2*thickness));
			currentLet++;
			break;
		case('P'):
			DrawVerticalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet,letPosition.y));
			DrawHorizontalBar(graphics, thickness, letSize-2*thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness,letPosition.y));
			DrawHorizontalBar(graphics, thickness, letSize-2*thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness,letPosition.y+(letSize-2*thickness)/3+thickness));
			DrawVerticalBar(graphics, thickness, (letSize-2*thickness)/3, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+letSize-thickness,letPosition.y+thickness));
			currentLet++;
			break;
		case('C'):
			DrawHorizontalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y));
			DrawVerticalBar(graphics, thickness, letSize-thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet,letPosition.y + thickness));
			DrawHorizontalBar(graphics, thickness, letSize-thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness, letPosition.y + letSize-thickness));
			currentLet++;
			break;
		case('G'):
			DrawHorizontalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y));
			DrawVerticalBar(graphics, thickness, letSize-thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet,letPosition.y + thickness));
			DrawHorizontalBar(graphics, thickness, letSize-thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness, letPosition.y + letSize-thickness));
			DrawVerticalBar(graphics, thickness, letSize/2, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+letSize-thickness, letPosition.y + letSize/2));
			DrawHorizontalBar(graphics, thickness, letSize/2, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+(letSize/2), letPosition.y + letSize/2));
			currentLet++;
			break;
		case('E'):
			DrawHorizontalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y));
			DrawVerticalBar(graphics, thickness, (letSize-3*thickness)/2, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y + thickness));
			DrawHorizontalBar(graphics, thickness, letSize,Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y+thickness+((letSize-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(letSize-3*thickness)/2, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y + thickness*2+((letSize-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, letSize,Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y+2*thickness + 2*((letSize-3*thickness)/2)));
			currentLet++;
			break;
		case('M'):
			DrawVerticalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet, letPosition.y));
			DrawDiagonalBar(graphics, thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+thickness, letPosition.y), 
				Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+letSize/2, letPosition.y+letSize/2));
			DrawDiagonalBar(graphics, thickness, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+letSize-thickness, letPosition.y), 
				Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+letSize/2-1.0f, letPosition.y+letSize/2));
			DrawVerticalBar(graphics, thickness, letSize, Vector2D(letPosition.x+letSize*currentLet+letGap*currentLet+letSize-thickness, letPosition.y));
		case(' '):
			currentLet++;
			break;
		}
		
	}
}

void Button::DrawHorizontalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition)
{

	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x, startPosition.y + i);
		Vector2D end(startPosition.x + size, startPosition.y+i);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void Button::DrawVerticalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x + i, startPosition.y);
		Vector2D end(startPosition.x + i, startPosition.y+size);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void Button::DrawDiagonalBar(Core::Graphics& graphics, float thickness, Vector2D startPosition, Vector2D endPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x, startPosition.y + i);
		Vector2D end(endPosition.x, endPosition.y +i);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void Button::UpdateButton(Vector2D mouse)
{
	if((mouse.x >= position.x && mouse.x <= position.x+newSize && 
			mouse.y >= position.y && mouse.y <= position.y+newSize/3 ))
	{
		int r =  (GetRValue(originalColor-30)<0)?0:GetRValue(originalColor-30);
		int g =  (GetGValue(originalColor-30)<0)?0:GetGValue(originalColor-30);
		int b =  (GetBValue(originalColor-30)<0)?0:GetBValue(originalColor-30);
		myColor = RGB(r,g,b); 
		if(Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
		{
			gameFrame.setFrame(true);
		}
	}
	else
	{
		myColor = RGB(GetRValue(originalColor), GetGValue(originalColor), GetBValue(originalColor));
	}
}