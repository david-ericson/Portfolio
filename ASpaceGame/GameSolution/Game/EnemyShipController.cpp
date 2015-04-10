#include "EnemyShipController.h"
#include "DebugMemory.h"
#include <cstdio>

EnemyShipController::EnemyShipController()
{
	firstWarningShown = false;
	secondWarningShown = false;
	startingPause = 3.0f;
	enemies = new EnemyShip[NUM_MAX_SHIPS];
	timeFromLastSpawn = spawnRate;
	for(int i=0; i<NUM_MAX_SHIPS; i++)
	{
		//set each enemy's position to a random vector within the screen
		enemies[i].setPosition(Vector2D(myRand.randomInRange(0, 1900.0f), myRand.randomInRange(0, 1000.0f)));
	}

}

EnemyShipController::~EnemyShipController()
{
	delete [] enemies;
}

void EnemyShipController::drawShips(Core::Graphics& graphics)
{
	for(int i=0; i<NUM_MAX_SHIPS; i++)
	{
		enemies[i].draw(graphics);
	}
	if(!firstWarningShown && totalTime >= 30)
	{
		gameAlerts.drawText(graphics,  10.0f, RGB(255, 149, 0), "New enemy detected", 40.0f, 5.0f, 0, Vector2D(250.0f, 900.0f));
		firstWarningShown =(totalTime >= 33);
	}
	if(!secondWarningShown && totalTime >= 60)
	{
		gameAlerts.drawText(graphics,  10.0f, RGB(255,149,0), "Enemy spawn times halved", 40.0f, 5.0f, 0, Vector2D(250.0f, 900.0f));
		if(totalTime >= 63)
		{
			secondWarningShown = true;
			spawnRate = spawnRate/2;
		}
	}

}

void EnemyShipController::updateShips(float dt, Vector2D& shipPosition, Bullets* bullets, int numBullets)
{
	if(startingPause<=0)
	{
		if(timeFromLastSpawn <= spawnRate)
		{
			timeFromLastSpawn += dt;
		}
	

		for(int i=0; i<NUM_MAX_SHIPS; i++)
		{
			if(enemies[i].isShipAlive())
			{

				enemies[i].update(dt, shipPosition, bullets, numBullets);

			}
			else if(timeFromLastSpawn >= spawnRate)
			{
				int type = (int)myRand.randomInRange(0, 100.0f);
				if(totalTime < 30.0f)
				{
					type = 1;
				}
				else
				{
					type = type<=50?1:type;
					type = type>50?2:type;
				}
				timeFromLastSpawn = 0;
				enemies[i].bringToLife(type);
				enemies[i].setPosition(Vector2D(myRand.randomInRange(0, 1900.0f), myRand.randomInRange(0, 1000.0f)));
			}
		}
	}
	else
	{
		startingPause -= dt;
	}
}

void EnemyShipController::resetShips()
{
	startingPause = 3.0f;
	spawnRate = 3.0f;
	timeFromLastSpawn = spawnRate;
	firstWarningShown = false;
	secondWarningShown = false;
	for(int i=0; i<NUM_MAX_SHIPS; i++)
	{
		enemies[i].resetShip();
	}
}