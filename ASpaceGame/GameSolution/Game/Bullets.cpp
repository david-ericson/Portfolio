#include "Bullets.h"

Bullets::Bullets() 
	{
		velocity = Vector2D(float(bulletSpeed), 0);
	}

void Bullets::drawBullet(Core::Graphics& graphics, Matrix3D transform)
{
	for(int i=0; i<numberOfBulletPoints; i++)
	{
		if(i + 1 < numberOfBulletPoints)
		{
			Vector2D start = transform * ammo[i];
			Vector2D end = transform * ammo[i+1];
			graphics.DrawLine(start.x, start.y, end.x, end.y);
		}
		else
		{
			Vector2D start = transform * ammo[i];
			Vector2D end = transform * ammo[0];
			graphics.DrawLine(start.x, start.y, end.x, end.y);
		}
	}
}

bool Bullets::isBulletOnScreen(int SCREEN_HEIGHT, int SCREEN_WIDTH)
{
	bool result;
	result = (((position.x + -2) < SCREEN_WIDTH )&&
		((position.x + 4) > 0 )&&
		((position.y + -2) < SCREEN_HEIGHT)&&
		((position.y + 2) > 0 ));
	return result;
}

void Bullets::setVelocity(Vector2D newVelocity)
{
	velocity = newVelocity;
}

void Bullets::setPosition(Vector2D newPosition)
{
	position = newPosition;
}

void Bullets::setAngle(float radians)
{
	angle = radians;
}

float Bullets::getAngle()
{
	return angle;
}

Vector2D Bullets::getPosition()
{
	return position;
}

void Bullets::moveBullet(float dt)
{
	position = position + velocity*dt;
}

void Bullets::resetBullet(float sentinel_value)
{
	position = Vector2D(sentinel_value, 0);
}

int Bullets::getDamage()
{
	setDamage();
	return damage;
}

void Bullets::setDamage()
{
	switch(bulletsUpgrade.getUpgradeCount())
	{
	case(0):
		damage = 1;
		break;
	case(1):
		damage = 2;
		break;
	case(2):
		damage = 3;
		break;
	case(3):
		damage = 5;
		break;
	case(4):
		damage = 8;
		break;
	case(5):
		damage = 12;
		break;
	}
}