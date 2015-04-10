#include "Backdrop.h"
#include <cstdio>

Backdrop::Backdrop(int width, int height)
{
	//asteroidRespawn = 15.0f;
	//angle = myRand.randomInRange(-0, 0);
	screen_width = float(width);
	screen_height = float(height);
	//asteroidVisible = false;
	//asteroidPosition = Vector2D(0,0);
	//asteroidVelocity.x = myRand.randomInRange(200.0f, 500.0f);
	//asteroidVelocity.y = 0;
	particles = new Particle[NUM_STARS];
	for(int i=0; i<NUM_STARS; i++)
	{
		particles[i].size = myRand.randomInRange(2.0f, 5.0f);
		particles[i].brightness = myRand.randomInRange(.15f, .35f);
		particles[i].position.x = myRand.randomInRange(0, float(width));
		particles[i].position.y = myRand.randomInRange(0, float(height));
	}
}

Backdrop::~Backdrop()
{
	delete [] particles;
}

void Backdrop::DrawBackdrop(Core::Graphics& graphics)
{
	for(int i=0; i<NUM_STARS; i++)
	{
		for(int j=0; j<particles[i].size+1; j++)
		{
			graphics.SetColor(randomColor.brightness(RGB(191,191,191), (particles[i].brightness)));
			Vector2D pointA(particles[i].position.x, particles[i].position.y - j);
			Vector2D pointB(particles[i].position.x+j, particles[i].position.y);
			Vector2D pointC(particles[i].position.x, particles[i].position.y + j);
			Vector2D pointD(particles[i].position.x-j, particles[i].position.y);
			graphics.DrawLine(pointA.x, pointA.y, pointB.x, pointB.y);
			graphics.DrawLine(pointB.x, pointB.y, pointC.x, pointC.y);
			graphics.DrawLine(pointC.x, pointC.y, pointD.x, pointD.y);
			graphics.DrawLine(pointD.x, pointD.y, pointA.x, pointA.y);
		}
	}
	/*if(asteroidVisible)
	{
		Matrix3D rotation = Rotate(angle);
		Matrix3D translate = Translate(asteroidPosition.x, asteroidPosition.y);
		Matrix3D transform = translate * rotation;

		
		for(int i=0; i<NUM_ASTEROID_POINTS; i++)
		{
			if(i+1 < NUM_ASTEROID_POINTS)
				{
					Vector2D start = transform * asteroidPoints[i];
					Vector2D end = transform * asteroidPoints[i+1];
					graphics.DrawLine(start.x, start.y, end.x, end.y);
				}
				else
				{
					Vector2D start = transform * asteroidPoints[i];
					Vector2D end = transform * asteroidPoints[0];
					graphics.DrawLine(start.x, start.y, end.x, end.y);
				}
		}
	}*/
}

void Backdrop::UpdateAsteroid(float dt)
{
	asteroidVisible=(isAsteroidOnScreen());
	if(asteroidVisible)
	{
		Matrix3D rotation = Rotate(angle);
		Vector2D newVelocity = rotation*asteroidVelocity*dt;
		asteroidPosition = asteroidPosition + newVelocity;
	}
}

bool Backdrop::isAsteroidOnScreen()
{
	return(((asteroidPosition.x + -20) < screen_width )&&
		((asteroidPosition.y + -10) < screen_height));
}
