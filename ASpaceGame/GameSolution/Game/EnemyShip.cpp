#include "EnemyShip.h"
#include "ParticleManager.h"
#include "movingTextManager.h"
#include "PlayerHealth.h"
#include "CashSystem.h"
#include <cstdio>

extern ParticleManager myParticles;
extern movingTextManager myText;
extern PlayerHealth healthBar;
extern CashSystem myCash;

EnemyShip::EnemyShip()
{
	playParticle = false;
	alive = false;
	worth = 200.0f;
	health = 5.0f;
	maxHealth = 5.0f;
	noCrashingTimer = 1.0f;
	velocity = Vector2D(600.0f, 0);
	position = Vector2D(700, 500);
	enemyType = 1;
	angle = 0;
}

void EnemyShip::draw(Core::Graphics& graphics)
{
	if(alive)
	{
		if(health > maxHealth/2)
		{
			float rValue = 255-(((health/maxHealth)-.5f) * 250);
			rValue = (rValue < 0)? 0: rValue;
			graphics.SetColor(RGB(rValue, 255, 0));
		}
		else
		{
			float gValue =  (((health)/(maxHealth/2))*250);
			gValue = gValue > 255?255:gValue;
			graphics.SetColor(RGB(255,gValue, 0));
		}
		drawShip(graphics);
	}
}

void EnemyShip::drawShip(Core::Graphics& graphics)
{
	Matrix3D rotation = Rotate(angle);
	Matrix3D translation = Translate(position.x, position.y);
	Matrix3D transform = translation * rotation;

	if(enemyType==1)
	{
		for(int i=0; i<NUM_STNDR_POINTS; i++)
		{
			if(i+1 < NUM_STNDR_POINTS)
			{
				Vector2D start = transform * standardEnemyPoints[i] ;
				Vector2D end = transform * standardEnemyPoints[i+1];
				graphics.DrawLine(start.x, start.y, end.x, end.y);
			}
			else
			{
				Vector2D start = transform * standardEnemyPoints[i];
				Vector2D end = transform * standardEnemyPoints[0];
				graphics.DrawLine(start.x, start.y, end.x, end.y);
			}
		}
	}
	if(enemyType==2)
	{
		for(int i=0; i<NUM_STRONG_POINTS; i++)
		{
			if(i+1 < NUM_STRONG_POINTS)
			{
				Vector2D start = transform * strongEnemyPoints[i] ;
				Vector2D end = transform * strongEnemyPoints[i+1];
				graphics.DrawLine(start.x, start.y, end.x, end.y);
			}
			else
			{
				Vector2D start = transform * strongEnemyPoints[i];
				Vector2D end = transform * strongEnemyPoints[0];
				graphics.DrawLine(start.x, start.y, end.x, end.y);
			}
		}
	}
}

void EnemyShip::update(float dt, const Vector2D& shipPosition, Bullets* bullets, int numBullets)
{
	/*Takes the position of our ship minus the position of the enemy. 
	It then checks to make sure that the enemy ship and player ship aren't ontop of each other.
	After that it simply sets the velocity, angle, and position of the enemy ship*/
	Vector2D targetPosition = (shipPosition - position);
	if(length(targetPosition) > hitRadius)
	{
		Vector2D newVelocity =  (normalized(targetPosition))*velocity.x;
		angle = (shipPosition.y >= position.y) ? acos(newVelocity.x/(velocity.x)) : -acos(newVelocity.x/(velocity.x));
		position = position + (newVelocity*dt);
		for(int i=0; i<numBullets; i++)
		{
			if(!playParticle)
			{
				checkDeath(&(bullets[i]));
			}
		}
	}
	else if(noCrashingTimer <= 0)
	{
		alive = false;
		switch(enemyType)
		{
		case(1):
			myParticles.addEffect(1, position, 300, 150.0f, 1.25f, RGB(212,28,56));
			break;
		case(2):
			myParticles.addEffect(1, position, 900, 150.0f, 1.25f, RGB(212,28,56));
			break;
		}
		healthBar.decreaseHealth(damage);
	}
	noCrashingTimer -= dt;

}

void EnemyShip::checkDeath(Bullets* thisBullet)
{
	if(thisBullet->alive)
	{
		if(lengthSquared(thisBullet->getPosition()-position) < hitRadius*hitRadius*2)
		{
			health -= thisBullet->getDamage();
			thisBullet->alive = false;
			playParticle = (health <= 0);
		}
		if(playParticle)
		{
			alive = false;
			switch (enemyType)
			{
			case(1):
				myParticles.addEffect(1, position, 300, 150.0f, 2.5f, RGB(199,95,199));
				myText.addText(3.0f, RGB(250, 215, 20), "+$200" ,20.0f, 5.0f, 1.0f, Vector2D(position.x-25.0f, position.y));
				break;
			case(2):
				myParticles.addEffect(1, position, 900, 150.0f, 2.5f, RGB(252,97,30));
				myText.addText(3.0f, RGB(250, 215, 20), "+$450" ,20.0f, 5.0f, 1.0f, Vector2D(position.x-25.0f, position.y));
				break;
			}
			myCash.increaseCash(worth);
		}
	}
}

void EnemyShip::setPosition(Vector2D newPosition)
{
	position = newPosition;
}

void EnemyShip::bringToLife(int type)
{
	enemyType = type;
	alive = true;
	playParticle = false;
	noCrashingTimer = 1.0f;
	switch(enemyType)
	{
	case(1):
		health = 2.0f+(int)(totalTime/15.0f);
		maxHealth = health;
		velocity = Vector2D(400.0f, 0);
		hitRadius = 10.0f;
		damage = 25.0f;
		worth = 200.0f;
		break;
	case(2):
		health = 25.0f+(int)(totalTime/15.0f);
		maxHealth = health;
		velocity = Vector2D(100.0f, 0);
		hitRadius = 30.0f;
		damage = 40.0f;
		worth = 450.0f;
		break;
	}
	
}

void EnemyShip::resetShip()
{
	playParticle = false;
	alive = false;
	noCrashingTimer = 1.0f;
	angle = 0;
}

Vector2D EnemyShip::getPosition()
{
	return position;
}

bool EnemyShip::isShipAlive()
{
	return alive;
}