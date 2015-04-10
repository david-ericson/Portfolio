#include <cstdio>
#include "Spaceship.h"
#include "ParticleManager.h"
#include "Profile.h"
#include "DebugMemory.h"
using namespace std;

using Core::Input;

extern ParticleManager myParticles;
extern bool paused;

Spaceship::Spaceship(Vector2D start) : GameObject(numShipLines, shipPoints) 
{
	originalPosition = start;
	position = start;
	fueling = false;
	alive = true;
	turretPoints = turret;
	timeFromLastShot = 1;
	mode = 1;
	bullets = new Bullets[maxBulletCount];
	for(int i=0; i<maxBulletCount; i++)
	{
		bullets[i].alive = false;
	}
}

Spaceship::~Spaceship()
{
	delete [] bullets;
}

void Spaceship::Draw (Core::Graphics& graphics)
{
	if(alive)
	{
		//Sets rotation, velocity, translation, transformation, and new position
		Vector2D mouse;
		mouse = Vector2D((float)(Core::Input::GetMouseX()), (float)(Core::Input::GetMouseY())); 
		//} 

		Matrix3D turretRotate = turretRotation(mouse);

		Matrix3D rotation = Rotate(angle);
		Matrix3D translation = Translate(position.x, position.y);
		Matrix3D transform = translation * rotation;
		Matrix3D turretTransform = translation * turretRotate;


		//Draw Spaceship
		{
			//PROFILE("Draw Ship");
			for(int i=0; i<numShipLines; i++)
			{
				if(i+1 < numShipLines)
				{
					Vector2D start = transform * shape.points[i];
					Vector2D end = transform * shape.points[i+1];
					graphics.DrawLine(start.x, start.y, end.x, end.y);
				}
				else
				{
					Vector2D start = transform * shape.points[i];
					Vector2D end = transform * shape.points[0];
					graphics.DrawLine(start.x, start.y, end.x, end.y);
				}
			}
		}

		for(int i=0; i<numberParticlEffects; i++)
		{
			thrusterTrail[i].Draw(graphics);
		}

		graphics.SetColor(RGB(255,100,0));
		//I put the drawing of the turret, bullets, and the game instructions in their own seperate draw functions.
		{
			//PROFILE("Draw Spaceship Turret");
			DrawTurret(graphics, turretTransform);
		}
		{
			//PROFILE("Draw Bullets");
			DrawBullets(graphics);
		}
		DrawInstruction(graphics);

	}

}

void Spaceship::DrawTurret (Core::Graphics& graphics, Matrix3D turretTransform)
{
	for(int i=0; i<numberTurretPoints; i++)
	{
		if(i+1 < numberTurretPoints)
		{
			Vector2D start = turretTransform * turret[i];
			Vector2D end = turretTransform * turret[i+1];
			graphics.DrawLine(start.x, start.y, end.x, end.y);
		}
		else
		{
			Vector2D start = turretTransform * turret[i];
			Vector2D end = turretTransform * turret[0];
			graphics.DrawLine(start.x, start.y, end.x, end.y);
		}
	}
}

void Spaceship::DrawBullets (Core::Graphics& graphics)
{
	for(int i=0; i<maxBulletCount; i++)
	{
		if(bullets[i].alive)
		{
			Vector2D bulletPosition = bullets[i].getPosition();
			Matrix3D translation = Translate(bulletPosition.x, bulletPosition.y);
			Matrix3D rotation = Rotate(bullets[i].getAngle());
			Matrix3D transform = translation * rotation;

			bullets[i].drawBullet(graphics, transform);
		}
	}
}

void Spaceship::DrawInstruction (Core::Graphics& graphics)
{
	graphics.SetColor(RGB(255,100,0));
}

Matrix3D Spaceship::turretRotation(Vector2D mouse)
{
	Matrix3D result;
	Vector2D distance = normalized(mouse - position);
	Vector2D perped = distance.perpcw();
	result.m[0][0] = distance.x;
	result.m[1][0] = distance.y;
	result.m[0][1] = perped.x;
	result.m[1][1] = perped.y;
	return result;
}

void Spaceship::wrapping(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	Vector2D smallest = shape.getSmallestValues();
	Vector2D largest = shape.getLargestValues();
	if(smallest.x + position.x > SCREEN_WIDTH){
		position.x = smallest.x+0;
	}
	if(largest.x + position.x < 0){
		position.x = largest.x + float(SCREEN_WIDTH);
	}
	if(smallest.y + position.y > SCREEN_HEIGHT){
		position.y = smallest.y + 0;
	}
	if(largest.y + position.y < 0){
		position.y = largest.y + (SCREEN_HEIGHT);
	}
}

void Spaceship::bouncing(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	if(position.x < 0){
		velocity.x *= -1;
	}
	if(position.x > SCREEN_WIDTH){
		velocity.x *=-1;
	}
	if(position.y < 0){
		velocity.y *= -1;
	}
	if(position.y > SCREEN_HEIGHT){
		velocity.y *=-1;
	}
}

void Spaceship::hitWall(Vector2D start, Vector2D finish, Vector2D newVelocity)
{
	Vector2D placement = position - start;
	Vector2D futurePlacement = (position+newVelocity)-start;
	Vector2D wall = start - finish;
	Vector2D perpWall = wall.perpcw();
	if((perpWall*placement)<0&&(perpWall*(futurePlacement)>0)||(perpWall*placement)>0&&(perpWall*(futurePlacement)<0))
		wallBounce(perpWall);
}

void Spaceship::wallBounce(Vector2D perpwall)
{
	perpwall = normalized(perpwall);
	float scalar = dotProduct(perpwall, velocity);
	Vector2D newVelocity = projectOnto(perpwall, scalar);
	velocity = newVelocity * -2;

	if(velocity.x < 1 && velocity.x >= 0)
		velocity.x = 2;
	if(velocity.x > -1 && velocity.x < 0)
		velocity.x = -.5f;
	if(velocity.y < 1 && velocity.y >= 0)
		velocity.y = 2;
	if(velocity.y > -1 && velocity.y < 0)
		velocity.y = -.5f;

	if(velocity.x > maxVelocity)
		velocity.x=maxVelocity;
	if(velocity.x < maxVelocity * -1)
		velocity.x= maxVelocity * -1;
	if(velocity.y > maxVelocity)
		velocity.y = maxVelocity;
	if(velocity.y < maxVelocity * -1)
		velocity.y = maxVelocity * -1;
}

void Spaceship::checkButtons(bool up, bool down, float dt)
{
	if((up && down)){
		velocity.y += 0;
	}
	if(!up && !down){
		if(velocity.y != 0){
			if(velocity.y < 2 && velocity.y > -2)
				velocity.y = 0;
			if(velocity.y < 0)
				velocity.y += 25*dt;
			if(velocity.y > 0)
				velocity.y += -25*dt;
		}
	}
}

void Spaceship::findVelocity(bool up, bool down, float dt)
{
	if(up && (velocity.y > maxVelocity*-1))
		velocity.y += -50*dt;
	if(down && (velocity.y < maxVelocity))
		velocity.y += 50*dt;

	//Checking if both or neither buttons for a specific direction are pressed, resulting in zero velocity.
	checkButtons(up, down, dt);
}

bool Spaceship::isFueling()
{
	return fueling;
}

void Spaceship::checkForFueling(Vector2D* fuelingStation)
{
	Vector2D smallest(1900.0f, 1900.0f);
	Vector2D largest(0, 0);
	for(int i=0; i<4; i++)
	{
		smallest.x = (fuelingStation[i].x < smallest.x) ? fuelingStation[i].x : smallest.x;
		smallest.y = (fuelingStation[i].y < smallest.y) ? fuelingStation[i].y : smallest.y;
		largest.x = (fuelingStation[i].x > largest.x) ? fuelingStation[i].x : largest.x;
		largest.y = (fuelingStation[i].y > largest.y) ? fuelingStation[i].y : largest.y;
	}
	fueling = ((position.x > smallest.x) && (position.x < largest.x) && (position.y > smallest.y) && (position.y < largest.y)); 
}

void Spaceship::setLife(bool life)
{
	alive = life;
}

void Spaceship::resetShip()
{
	position = originalPosition;
	fueling = false;
	alive = true;
	timeFromLastShot = 1;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<100; j++)
		{
			thrusterTrail[i].particles[j].lifetime = 0.01f;
		}
	}
	angle = 0;
}

void Spaceship::update (float dt, const int SCREEN_HEIGHT, const int SCREEN_WIDTH, Vector2D* fuelingStation)
{
	if(alive&&!paused)
	{
		static bool space;
		bool up, down, a, d, leftMouse = false;
		up = (Input::IsPressed(Input::KEY_UP)||Input::IsPressed(87));
		down = (Input::IsPressed(Input::KEY_DOWN)||Input::IsPressed(83));
		a = (Input::IsPressed(65)||Input::IsPressed(Input::KEY_LEFT));
		d = (Input::IsPressed(68)||Input::IsPressed(Input::KEY_RIGHT));
		leftMouse = (Input::IsPressed(Input::BUTTON_LEFT));

		POINT cursor;
		Vector2D mouse;
		if(GetCursorPos(&cursor)){}
		mouse = Vector2D((float)(Core::Input::GetMouseX()), (float)(Core::Input::GetMouseY())); 

		if(a){
			angle += -rotateAmount;
		}

		if(d){
			angle += rotateAmount;
		}

		if(timeFromLastShot <= fireRate)
		{
			timeFromLastShot += dt;
		}

		if(leftMouse && !fueling && !paused)
		{
			for(int i=0; i<maxBulletCount; i++)
			{
				Vector2D bulletsPosition = bullets[i].getPosition();
				if(!bullets[i].alive) 
				{
					if(timeFromLastShot>= fireRate){
						timeFromLastShot = 0;
						bullets[i].alive = true;
						Matrix3D rotation = turretRotation(mouse);
						bullets[i].setPosition(position + (rotation * Vector2D(float(turretLength), 0)));
						bullets[i].setVelocity(rotation * Vector2D(float(bulletSpeed),0));
						if(mouse.y < position.y){
							bullets[i].setAngle( -acos(rotation.m[0][0])); 
						}
						else{
							bullets[i].setAngle( acos(rotation.m[0][0])); 
						}

					}
				}
			}
		}
		//Checking for turret movement

		findVelocity(up, down, dt);

		//Wrapping off the arbitrary boundaries.
		if(mode == 1)
		{
			wrapping(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		//Bouncing off the arbitrary boundaries.
		if(mode == 2)
		{
			bouncing(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		Vector2D newVelocity = Rotate(angle) * velocity;

		checkForFueling(fuelingStation);

		for(int i=0; i<maxBulletCount; i++)
		{

			if(bullets[i].isBulletOnScreen(SCREEN_HEIGHT, SCREEN_WIDTH) && bullets[i].alive)
			{
				bullets[i].moveBullet(dt);
			}
			else
			{
				bullets[i].alive = false;
			}
		}

		newVelocity = Rotate(angle) * velocity;

		position = position + newVelocity;

		for(int i=0; i<numberParticlEffects; i++)
		{
			thrusterTrail[i].Update(dt);
			if(i == 0)
			{
				Vector2D newPosition = position + (Rotate(angle) * (Vector2D(0, shape.getLargestValues().y+2.5f) - Vector2D(10,0)));
				thrusterTrail[i].CheckandCreateNewParticles(newPosition, angle);
			}
			if(i == 1)
			{
				Vector2D newPosition = position + (Rotate(angle) * (Vector2D(0, shape.getLargestValues().y+2.5f) + Vector2D(10,0)));
				thrusterTrail[i].CheckandCreateNewParticles(newPosition, angle);
			}
		}
	}
}