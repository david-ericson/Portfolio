#include "Upgrade.h"
#include <cstdio>

Upgrade::Upgrade(const char* info, Vector2D startPosition, int upgradeType)
{
	type = upgradeType;
	upgradeCount = 0;
	upgradeCooldown = .5f;
	text = info;
	position = startPosition;
	costPosition = Vector2D(position.x + (float)(BOX_SIZE/10), position.y+7*(float)(BOX_SIZE/10));
	myColor = RGB(94, 94, 94);
}

void Upgrade::DrawUpgrade(Core::Graphics& graphics, Vector2D mouse, float thickness)
{
	myColor = (CheckMouse(mouse))? RGB(134, 134, 134): RGB(94,94,94);
	
	if(upgradeCooldown < .5)
	{
		upgradeCooldown += .016f;
	}
	graphics.SetColor(myColor);
	for(int i=0; i<BOX_SIZE; i++)
	{
		Vector2D start(position.x + i, position.y);
		Vector2D end(position.x + i, position.y+BOX_SIZE);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
	if(CheckMouse(mouse))
	{
		viewText(graphics);
		if(Core::Input::IsPressed(Core::Input::BUTTON_LEFT)&&upgradeCooldown >= .5f && myCash.getCash() >= upgradeCost && upgradeCount < 5)
		{
			upgradeCooldown = 0;
			myCash.decreaseCash(upgradeCost);
			upgradeCount++;
		}
	}
	SetUpgradeCost();
	DrawGraphic(graphics);
	graphics.SetColor(RGB(255,255,255));
	if(upgradeCount > 4)
	{
		graphics.SetColor(RGB(255,0,0));
	}
	//Draws $
	DrawHorizontalBar(graphics, thickness, Letter_Size, Vector2D(costPosition.x, costPosition.y+thickness/2));
	DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2, Vector2D(costPosition.x, costPosition.y + thickness));
	DrawHorizontalBar(graphics, thickness, Letter_Size, Vector2D(costPosition.x, costPosition.y+thickness+((Letter_Size-3*thickness)/2)));
	DrawVerticalBar(graphics, thickness,(Letter_Size-3*thickness)/2, Vector2D(costPosition.x+(Letter_Size-thickness), costPosition.y + thickness*2+((Letter_Size-3*thickness)/2)));
	DrawHorizontalBar(graphics, thickness, Letter_Size, Vector2D(costPosition.x, costPosition.y+2*thickness + (2*((Letter_Size-3*thickness)/2)-thickness/2)));
	DrawVerticalBar(graphics, thickness, Letter_Size, Vector2D(costPosition.x+(Letter_Size/2.5f), costPosition.y));
	//Draws Cost
	DrawLetters(graphics, thickness);
}

void Upgrade::DrawGraphic(Core::Graphics& graphics)
{
	if(type==armor)
	{
		graphics.SetColor(RGB(255,242,59));
		DrawGraphicPoints(graphics, armorGraphic, armorSize);
	}
	else if(type==fuel)
	{
		graphics.SetColor(RGB(219,65,31));
		DrawGraphicPoints(graphics, fuelGraphic, fuelSize);
	}
	else if(type == health)
	{
		graphics.SetColor(RGB(103, 219, 31));
		DrawGraphicPoints(graphics, healthGraphic, healthSize);
	}
	else if(type == bullet)
	{
		graphics.SetColor(RGB(46, 46, 46));
		DrawGraphicPoints(graphics, bulletGraphic, bulletSize);
	}
}

void Upgrade::DrawGraphicPoints(Core::Graphics& graphics, Vector2D* points, int numPoints)
{
	for(int i=0; i<numPoints; i++)
		{
			if(i+1 < numPoints)
			{
				Vector2D start =  points[i]+position;
				Vector2D end =  points[i+1]+position;
				graphics.DrawLine(start.x, start.y, end.x, end.y);
			}
			else
			{
				Vector2D start = points[i]+position;
				Vector2D end = points[0]+position;
				graphics.DrawLine(start.x, start.y, end.x, end.y);
			}
		}
}

void Upgrade::DrawLetters(Core::Graphics& graphics, float thickness)
{
	char buf[50];
	sprintf_s(buf, "%f", upgradeCost);
	graphics.DrawString(0,0, buf);
	atTheDot = false;
	int currentLetter = 1;
	for(int i=0; i<50; i++)
	{
		if(!atTheDot)
		{
			switch(buf[i])
			{
			case('0'):
				DrawVerticalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap, costPosition.y));
				DrawVerticalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap+(Letter_Size-thickness), costPosition.y));
				DrawHorizontalBar(graphics, thickness, Letter_Size-2*thickness, 
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap+thickness, costPosition.y));
				DrawHorizontalBar(graphics, thickness, Letter_Size-2*thickness, 
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap+thickness, costPosition.y+(Letter_Size-thickness)));
				currentLetter++;
				break;
			case('1'):
				DrawHorizontalBar(graphics, thickness, (Letter_Size-thickness)/4, 
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap+ (Letter_Size-thickness)/4, costPosition.y+(Letter_Size-thickness)/4));
				DrawVerticalBar(graphics, thickness, Letter_Size-thickness, 
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap+((Letter_Size-thickness)/2), costPosition.y));
				DrawHorizontalBar(graphics, thickness, Letter_Size-thickness*2,
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap+(Letter_Size-thickness)/4, costPosition.y+Letter_Size-thickness));
				currentLetter++;
				break;
			case('2'):
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y));
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+(Letter_Size-thickness), costPosition.y + thickness));
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+thickness+((Letter_Size-3*thickness)/2)));
				DrawVerticalBar(graphics, thickness,(Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y + thickness*2+((Letter_Size-3*thickness)/2)));
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+2*thickness + 2*((Letter_Size-3*thickness)/2)));
				currentLetter++;
				break;
			case('3'):
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y));
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+(Letter_Size-thickness), costPosition.y + thickness));
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+thickness+((Letter_Size-3*thickness)/2)));
				DrawVerticalBar(graphics, thickness,(Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+(Letter_Size-thickness), costPosition.y + thickness*2+((Letter_Size-3*thickness)/2)));
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+2*thickness + 2*((Letter_Size-3*thickness)/2)));
				currentLetter++;
				break;
			case('4'):
				DrawVerticalBar(graphics, thickness, ((Letter_Size-thickness)/2)+thickness, 
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap, costPosition.y));
				DrawHorizontalBar(graphics, thickness, Letter_Size-thickness*2, 
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap+thickness, costPosition.y+((Letter_Size-thickness)/2)));
				DrawVerticalBar(graphics, thickness, Letter_Size,
					Vector2D(costPosition.x+currentLetter*Letter_Size+currentLetter*Letter_Gap+(Letter_Size-thickness), costPosition.y));
				currentLetter++;
				break;
			case('5'):
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y));
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y + thickness));
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+thickness+((Letter_Size-3*thickness)/2)));
				DrawVerticalBar(graphics, thickness,(Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+(Letter_Size-thickness), costPosition.y + thickness*2+((Letter_Size-3*thickness)/2)));
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+2*thickness + 2*((Letter_Size-3*thickness)/2)));
				currentLetter++;
				break;
			case('6'):
				DrawVerticalBar(graphics, thickness, Letter_Size,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y));
				DrawHorizontalBar(graphics, thickness, Letter_Size-thickness, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+thickness, costPosition.y));
				DrawHorizontalBar(graphics, thickness, Letter_Size-thickness,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+thickness, costPosition.y+((Letter_Size-3*thickness)/2)+thickness));
				DrawHorizontalBar(graphics, thickness, Letter_Size-thickness,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+thickness, costPosition.y+(Letter_Size-3*thickness)+2*thickness));
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+(Letter_Size-thickness), costPosition.y+((Letter_Size-3*thickness)/2)+2*thickness));
				currentLetter++;
				break;
			case('7'):
				DrawVerticalBar(graphics, thickness, Letter_Size,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+Letter_Size-thickness, costPosition.y));
				DrawHorizontalBar(graphics, thickness, Letter_Size-thickness,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y));
				currentLetter++;
				break;
			case('8'):
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y));
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y + thickness));
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+Letter_Size-thickness, costPosition.y + thickness));
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+thickness+((Letter_Size-3*thickness)/2)));
				DrawVerticalBar(graphics, thickness,(Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+(Letter_Size-thickness), costPosition.y + thickness*2+((Letter_Size-3*thickness)/2)));
				DrawVerticalBar(graphics, thickness,(Letter_Size-3*thickness)/2, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y + thickness*2+((Letter_Size-3*thickness)/2)));
				DrawHorizontalBar(graphics, thickness, Letter_Size, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+2*thickness + 2*((Letter_Size-3*thickness)/2)));
				currentLetter++;
				break;
			case('9'):
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2+2*thickness,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y));
				DrawHorizontalBar(graphics, thickness, Letter_Size-thickness, 
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+thickness, costPosition.y));
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+(Letter_Size-thickness), costPosition.y+thickness));
				DrawHorizontalBar(graphics, thickness, Letter_Size-thickness,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+thickness, costPosition.y+((Letter_Size-3*thickness)/2)+thickness));
				DrawHorizontalBar(graphics, thickness, Letter_Size,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter, costPosition.y+(Letter_Size-3*thickness)+2*thickness));
				DrawVerticalBar(graphics, thickness, (Letter_Size-3*thickness)/2,
					Vector2D(costPosition.x+Letter_Size*currentLetter+Letter_Gap*currentLetter+(Letter_Size-thickness), costPosition.y+((Letter_Size-3*thickness)/2)+2*thickness));
				currentLetter++;
				break;
			case('.'):
				atTheDot=true;
				break;
			}
		}
	}
}

void Upgrade::DrawHorizontalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x, startPosition.y + i);
		Vector2D end(startPosition.x + size, startPosition.y+i);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void Upgrade::DrawVerticalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x + i, startPosition.y);
		Vector2D end(startPosition.x + i, startPosition.y+size);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void Upgrade::DrawDiagonalBar(Core::Graphics& graphics, float thickness, Vector2D endPosition, Vector2D startPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x, startPosition.y + i);
		Vector2D end(endPosition.x, endPosition.y + i);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

bool Upgrade::CheckMouse(Vector2D mouse)
{
	return((mouse.x >= position.x && mouse.x <= position.x+BOX_SIZE && 
			mouse.y >= position.y && mouse.y <= position.y+BOX_SIZE ));
}

void Upgrade::viewText(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(6, 196, 130));
	graphics.DrawLine(position.x + (float)BOX_SIZE/2, position.y + (float)BOX_SIZE/4, position.x + (float)BOX_SIZE/2+50.0f, position.y - 200.0f);
	graphics.DrawLine(position.x + (float)BOX_SIZE/2+50.0f, position.y - 200.0f, position.x+(float)BOX_SIZE/2+400.0f, position.y-200.0f);
	if(type == armor)
	{
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-180.0f), "The armor upgrade increases the rate");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-160.0f), "at which your armor regens out of combat.");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-140.0f), "Your ship regens no armor until the first");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-120.0f), "upgrade has been purchased. The ship is");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-100.0f), "'out of combat' when you haven't taken");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-80.0f), "damage in over five seconds.");
	}	
	else if(type == fuel)
	{
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-180.0f), "The fuel upgrade increases the overall");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-160.0f), "efficiency of your spacecraft. What this");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-140.0f), "acutally means is that your fuel doesn't");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-120.0f), "drain like a Hummer's anymore. You've");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-100.0f), "gotta love that one mile to the gallon.");
	}	
	else if(type == health)
	{
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-180.0f), "The repair upgrade increases the rate");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-160.0f), "at which these small sort-of space wrenches");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-140.0f), "spawn that increase your ship's health");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-120.0f), "when picked up. The first upgrade causes");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-100.0f), "the wrenches to start spawning whilst");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-80.0f), "continual upgrades decrease the spawn time.");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-60.0f), "Spawn times (seconds): 60/45/30/20/15. ");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-40.0f), "WARNING: The spawn time resets when ");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-20.0f), "you purchase this upgrade to the new time.");
	}
	else if(type == bullet)
	{
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-180.0f), "The bullet upgrade increases the damage ");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-160.0f), "that your bullets deal to targets. Oh ");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-140.0f), "yeah by the way the enemies' health scale");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-120.0f), "as the time goes on so this upgrade might be ");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-100.0f), "a good idea, just saying.");
		graphics.DrawString(int(position.x + (float)BOX_SIZE/2+100.0f), int(position.y-80.0f), "Damage: 1(no upgrades)/2/3/5/8/12");
	}
}

void Upgrade::resetUpgrade()
{
	upgradeCount = 0;
}

void Upgrade::SetUpgradeCost()
{
	if(type==armor)
	{
		switch(upgradeCount)
		{
		case(0):
			upgradeCost = 500.0f;
			break;
		case(1):
			upgradeCost = 1500.0f;
			break;
		case(2):
			upgradeCost = 5000.0f;
			break;
		case(3):
			upgradeCost = 10000.0f;
			break;
		case(4):
			upgradeCost = 20000.0f;
			break;
		}
	}
	if(type==fuel)
	{
		switch(upgradeCount)
		{
		case(0):
			upgradeCost = 750.0f;
			break;
		case(1):
			upgradeCost = 1250.0f;
			break;
		case(2):
			upgradeCost = 2500.0f;
			break;
		case(3):
			upgradeCost = 6000.0f;
			break;
		case(4):
			upgradeCost = 10000.0f;
			break;
		}
	}
	if(type==health)
	{
		switch(upgradeCount)
		{
		case(0):
			upgradeCost = 900.0f;
			break;
		case(1):
			upgradeCost = 2700.0f;
			break;
		case(2):
			upgradeCost = 5000.0f;
			break;
		case(3):
			upgradeCost = 9000.0f;
			break;
		case(4):
			upgradeCost = 15000.0f;
			break;
		}
	}
	if(type==bullet)
	{
		switch(upgradeCount)
		{
		case(0):
			upgradeCost = 900.0f;
			break;
		case(1):
			upgradeCost = 1500.0f;
			break;
		case(2):
			upgradeCost = 5000.0f;
			break;
		case(3):
			upgradeCost = 9500.0f;
			break;
		case(4):
			upgradeCost = 17000.0f;
			break;
		}
	}
}

int Upgrade::getUpgradeCount()
{
	return upgradeCount;
}
