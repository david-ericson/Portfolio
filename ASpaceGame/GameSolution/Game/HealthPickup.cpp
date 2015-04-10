#include "HealthPickup.h"
#include "ParticleManager.h"

extern ParticleManager myParticles;

HealthPickup::HealthPickup()
{
	alive = false;
	setIncrement = true;
	lastUpgradeCount = 0;
	spawnIncrement = 10000.0f;
	lifetime = 5.0f;
	healAmount = 25.0f;
	position.x = myRand.randomInRange(50.0f, 1850.0f);
	position.y = myRand.randomInRange(50.0f, 950.0f);
}

void HealthPickup::DrawHealthPickup(Core::Graphics& graphics)
{
	if(alive){
		for(int i=0; i<numWrenchPoints; i++)
		{
			graphics.SetColor(RGB(98,217,133));
			if(i+1<numWrenchPoints)
			{
				Vector2D start(position.x+wrenchPoints[i].x, position.y + wrenchPoints[i].y);
				Vector2D end(position.x + wrenchPoints[i+1].x, position.y + wrenchPoints[i+1].y);
				graphics.DrawLine(start.x, start.y, end.x, end.y);
			}
			else
			{
				Vector2D start(position.x+wrenchPoints[i].x, position.y + wrenchPoints[i].y);
				Vector2D end(position.x + wrenchPoints[0].x, position.y + wrenchPoints[0].y);
				graphics.DrawLine(start.x, start.y, end.x, end.y);
			}
		}
	}
}

void HealthPickup::UpdateHealthPickup(float dt, Vector2D& shipPosition)
{
	distance = 9.999f;
	if(!paused)
		{
		checkLife(dt);
		if(alive)
		{
			if(lengthSquared(shipPosition -  position) < 850.0f)
			{
				alive = false;
				healthBar.increaseHealth(healAmount);
			}
			lifetime -= dt;
		}
	}
}

void HealthPickup::bringToLife()
{
	alive = true;
	lifetime = 10.0f;
	position.x = myRand.randomInRange(50.0f, 1850.0f);
	position.y = myRand.randomInRange(50.0f, 950.0f);
	myParticles.addEffect(3, position, 300, 0,0, RGB(29, 209, 41));
}

bool HealthPickup::getLife()
{
	return alive;
}

void HealthPickup::resetHealthDrop()
{
	alive = false;
	setIncrement = true;
	lastUpgradeCount = 0;
	spawnIncrement = 10000.0f;
}

void HealthPickup::checkLife(float dt)
{
	if(!setIncrement || (lastUpgradeCount==0 && healthDropUpgrade.getUpgradeCount() > 0))
	{
		lastUpgradeCount = float(healthDropUpgrade.getUpgradeCount());
		switch(healthDropUpgrade.getUpgradeCount())
		{
		
		case(1):
			spawnIncrement=60.0f;
			setIncrement = true;
			break;
		case(2):
			spawnIncrement=45.0f;
			setIncrement = true;
			break;
		case(3):
			spawnIncrement=30.0f;
			setIncrement=true;
			break;
		case(4):
			spawnIncrement=20.0f;
			setIncrement=true;
			break;
		case(5):
			spawnIncrement=15.0f;
			setIncrement=true;
			break;
		}
	}
	if(spawnIncrement > 0)
	{
		spawnIncrement -= dt;
	}
	else
	{
		bringToLife();
		setIncrement = false;
	}
	
}