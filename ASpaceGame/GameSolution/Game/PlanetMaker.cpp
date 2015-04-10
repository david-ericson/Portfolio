#include "PlanetMaker.h"
#include "ParticleManager.h"
#include "DebugMemory.h"

extern ParticleManager myParticles;

PlanetMaker::PlanetMaker()
	{
		numPlanetPoints = numberPlanetPoints;
		planetPoints = planetsPoints;
		supernova = false;
		sunLifespan = 90;
		hasSun = true;
		sunColor = RGB(200,40, 40);
		planetColor = RGB(200,10,10);
		planets = new Planet[numPlanets];
		for(int i=0; i<numPlanets; i++)
		{
			planets[i].planetPoints = planetPoints;
			planets[i].orbitDistance = 0;
			planets[i].numPlanetPoints = numPlanetPoints;
			planets[i].scale = .15f;
			planets[i].angle = 0;
			planets[i].increment = int(myRand.randomInRange(-4.0f, 4.0f));
			if(planets[i].increment == 0)
			{
				planets[i].increment = 1;
			}
		}
		makePlanet(numPlanets);
	}

PlanetMaker::~PlanetMaker()
	{
		delete [] planets;
	}

void PlanetMaker::makePlanet(int planetsLeft)
{
	if(planetsLeft > 0)
	{
		int positioner = numPlanets - planetsLeft;
		if(positioner > 0){
			planets[positioner].planetPoints = planetPoints;
			planets[positioner].orbitDistance = (float(400)/float(positioner));
			planets[positioner].numPlanetPoints = numPlanetPoints;
		}
		else
		{
			planets[positioner].planetPoints = planetPoints;
			planets[positioner].orbitDistance = 0;
			planets[positioner].numPlanetPoints = numPlanetPoints;
		}
		if(positioner > 0){
			planets[positioner].scale = (float(planetsLeft)/float(numPlanets)/9);
		}
		makePlanet(planetsLeft - 1);
	}
	
}

void PlanetMaker::DrawPlanets(Core::Graphics& graphics)
{
	for(int i=0; i<numPlanets; i++)
	{
		if(i==0)
		{
			if(sunLifespan>0)
			{
				graphics.SetColor(randColor.brightness(sunColor, 90/sunLifespan));
			}
		}
		else
		{
			graphics.SetColor(planetColor);
		}
		if(i!=0 || sunLifespan > 0)
			planets[i].DrawPlanet(graphics);
	}
}

void PlanetMaker::UpdatePlanets(float dt)
{
	if(sunLifespan > 0 || supernova)
	{
		sunLifespan -= dt;
	}
	else
	{
		supernova = true;
		myParticles.addEffect(1, Vector2D(350,300), 1000, 750.0f, 10.0f, RGB(214, 127, 84));
	}
	for(int i=0; i<numPlanets; i++)
	{
		if(i-1 >= 0)
			planets[i].UpdatePlanet(dt, planets[i-1].position);
		else
			planets[i].UpdatePlanet(dt, Vector2D(350,300));
	}
}

void PlanetMaker::resetPlanets()
{
	supernova = false;
	sunLifespan = 90;
	hasSun = true;
	makePlanet(numPlanets);
}