#include "GameplayFrame.h"

GameplayFrame::GameplayFrame()
{
	currentFrame = false;
	paused = true;
	instructionsPause = true;
	upgradesPause = false;
	shipDeathTimer = 2.0f;
}

bool GameplayFrame::UpdateGame(float dt)
{
	PROFILE("Total Update");
	mouse = Vector2D((float)(Core::Input::GetMouseX()), (float)(Core::Input::GetMouseY()));
	myBackground.UpdateAsteroid(dt);
	if((Input::IsPressed(82) && pauseToggleCooldown <= 0) && !instructionsPause && !alreadyKilled)
	{
		paused = !paused;
		upgradesPause = !upgradesPause;
		pauseToggleCooldown = .5f;
	}
	else if((Input::IsPressed(73) && pauseToggleCooldown <= 0) && !upgradesPause && !alreadyKilled)
	{
		paused = !paused;
		instructionsPause = !instructionsPause;
		pauseToggleCooldown = .5f;
	}
	else if(pauseToggleCooldown > 0)
	{
		pauseToggleCooldown -= dt;
	}
	float time = (!paused) ? dt: 0;

	Timer profileTimer;
	profiler.newFrame();
	debugTime = 1/(counter.getLastTimeInterval());
	profileTimer.startTimer();
	{
		PROFILE("Ship Update");
		ranger.update(time, SCREEN_HEIGHT, SCREEN_WIDTH, fuelStation);
	}
	{
		PROFILE("Planets Update");
		creator.UpdatePlanets(time);
	}
	{
		PROFILE("Enemies Update");
		tester.updateShips(time, ranger.position, ranger.bullets,10);
	}
	{
		PROFILE("Particles Update");
		myParticles.updateEffect(time);
	}
	if(!paused && !alreadyKilled)
	{
		totalTime += time;
	}
	if(!alreadyKilled)
	{
		fuelGauge.UpdateFuel(time, ranger.isFueling());
		healthBar.UpdateArmor(time);
	}
	healthDrop.UpdateHealthPickup(time, ranger.position);
	if(Input::IsPressed(Input::KEY_ESCAPE))
	{
		return true;
	}
	if(healthBar.getHealth() <= 0 || fuelGauge.getFuel()<= 0)
	{
		if(!alreadyKilled)
		{
			ranger.setLife(false);
			myParticles.addEffect(1, ranger.position, 500, 350.0f, 3.0f, RGB(242, 165, 22));
			shipDeathTimer -= dt;
			alreadyKilled = (shipDeathTimer <= 0);
		}
	}
	myText.updateText(time);
	return false;
}

void GameplayFrame::DrawGame(Core::Graphics& graphics)
{
	PROFILE("Total Draw");
	myBackground.DrawBackdrop(graphics);
	graphics.SetColor( RGB( 255, 255, 255));
	char buf[50];
	sprintf_s(buf, "%f", debugTime);
	graphics.DrawString(35,980, buf);
	graphics.DrawString(5, 980, "FPS:");
	healthBar.DrawHealth(graphics);
	fuelGauge.DrawPlayerFuel(graphics);
	graphics.SetColor(RGB(51,51,51));
	boundaries.Draw(graphics);
	{
		PROFILE("Draw Planets");
		creator.DrawPlanets(graphics);
	}
	graphics.SetColor( RGB( 255, 255, 255));
	{
		PROFILE("Draw Enemies");
		tester.drawShips(graphics);
	}
	{
		PROFILE("Draw Particles");
		myParticles.drawEffect(graphics);
	}
	myText.drawText(graphics);
	graphics.SetColor(RGB(255,255,255));
	Vector2D fuel(fuelStation[1].x+(fuelStation[3].x-fuelStation[1].x)/4.5f, (fuelStation[0].y + ((fuelStation[2].y-fuelStation[0].y)/2.5f)));
	gameText.drawText(graphics, 4.0f, RGB(255,255,255), "Fueling", 20.0f, 5.0f, 0, fuel);
	gameText.drawText(graphics, 4.0f, RGB(255,255,255), "Station", 20.0f, 5.0f, 0, Vector2D(fuel.x, fuel.y + 35.0f));
	myCash.DrawCash(graphics, 5.0f);
	healthDrop.DrawHealthPickup(graphics);
	graphics.SetColor( RGB(255, 255, 255));
	graphics.DrawString(30, 100, "PRESS I TO OPEN/CLOSE THE LIST OF INSTRUCTIONS.");
	DebugFrameMemory(graphics);
	graphics.SetColor( RGB( 255, 100, 0));
	{
		ranger.Draw(graphics);
	}
	//rapidFirePowerup.drawPowerup(graphics);
	if(alreadyKilled)
	{
		char buf[50];
		sprintf_s(buf, "You survived for %i seconds!", (int)totalTime);
		Core::RGB textColor = RGB(255, 149, 0);
		gameText.drawText(graphics,  5.0f, textColor, "GAME OVER...", 30.0f, 5.0f, 0, Vector2D(250.0f, 250.0f));
		gameText.drawText(graphics,  5.0f, textColor, buf, 30.0f, 5.0f, 0, Vector2D(680.0f, 250.0f));
		graphics.SetColor(RGB(255,100,0));
		graphics.DrawString(700, 500, "Game over, you have died and as thus you are");
		graphics.DrawString(700, 520, "reading this screen. If you wish to try again");
		graphics.DrawString(700, 540, "simply press the space bar to reset the game. Yep...");
		graphics.DrawString(700, 560, "why are you still reading this?? I mean I");
		graphics.DrawString(700, 580, "don't care but you are kind of wasting your");
		graphics.DrawString(700, 600, "time at this point.");
		if(Core::Input::IsPressed(32))
		{
			resetFrame();
		}
	}
	if(paused && upgradesPause)
	{
		armorUpgrade.DrawUpgrade(graphics, mouse, 3.0f);
		healthDropUpgrade.DrawUpgrade(graphics, mouse, 3.0f);
		bulletsUpgrade.DrawUpgrade(graphics, mouse, 3.0f);
		fuelUpgrade.DrawUpgrade(graphics, mouse, 3.0f);
	}
	else if(paused && instructionsPause)
	{
		graphics.DrawString(825, 430, "	(Press I to close/open the list of instructions.)");
		graphics.DrawString(800, 450, "	Instructions: use up, down, W or S to move the ship. A and D");
		graphics.DrawString(800, 470, "or left and right to rotate the spaceship. Use the left mouse");
		graphics.DrawString(800, 490, "to fire your turret. Keep in mind that only ten bullets can");
		graphics.DrawString(800, 510, "be on the screen at once and that the sun in the background");
		graphics.DrawString(800, 530, "is simply for ambiance.");
		graphics.DrawString(800, 570, "	Upgrades: Use the cash that you have earned to purchase");
		graphics.DrawString(800, 590, "the upgrades. To open the upgrade menu press R. You can");
		graphics.DrawString(800, 610, "view individual upgrade information by hovering over the tiles.");
		graphics.DrawString(800, 650, "Fueling: Your fuel will slowly decrease as time goes on...because");
		graphics.DrawString(800, 670, "you know.....space....well anyway drive over the aptly named");
		graphics.DrawString(800, 690, "'FUELING STATION' to fuel your ship. You can't, however, fire");
		graphics.DrawString(800, 710, "your turret while you are fueling, because that is illegal.");
		graphics.DrawString(800, 750, "Damage: When an enemy ship collides with you, you'll take");
		graphics.DrawString(800, 770, "some damage. If you have the armor upgrades then your armor");
		graphics.DrawString(800, 790, "will absorb the first chuncks of damage. Each ship has a");
		graphics.DrawString(800, 810, "one second spawn delay from being able to damage your ship");
		graphics.DrawString(800, 830, "as well as a three second delay from the game starting to");
		graphics.DrawString(800, 850, "being able to damage your spacecraft.");
	}

}

void GameplayFrame::DebugFrameMemory(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(255,255,255));
	_CrtMemState myState;
	_CrtMemCheckpoint(&myState);
	myState.lCounts;
	char buf[50];
	sprintf_s(buf, "Current count: %i", myState.lCounts[_CLIENT_BLOCK]);
	graphics.DrawString(20, 870, buf);
	sprintf_s(buf, "Current size: %i", myState.lSizes[_CLIENT_BLOCK]);
	graphics.DrawString(20, 890, buf);
	sprintf_s(buf, "Current HighWaterCount: %i", myState.lHighWaterCount);
	graphics.DrawString(20, 910, buf);
}

bool GameplayFrame::getFrame()
{
	return currentFrame;
}

void GameplayFrame::resetFrame()
{
	ranger.resetShip();
	creator.resetPlanets();
	tester.resetShips();
	myCash.resetCash();
	armorUpgrade.resetUpgrade();
	healthDropUpgrade.resetUpgrade();
	bulletsUpgrade.resetUpgrade();
	fuelUpgrade.resetUpgrade();
	healthBar.resetHealth();
	fuelGauge.resetFuel();
	healthDrop.resetHealthDrop();
	myParticles.resetEffects();
	myText.resetText();
	alreadyKilled = false;
	totalTime = 0;
	shipDeathTimer = 2.0f;
}

void GameplayFrame::setFrame(bool value)
{
	currentFrame = value;
}