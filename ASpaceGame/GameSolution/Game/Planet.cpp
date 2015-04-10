#include "Planet.h"

void Planet::DrawPlanet(Core::Graphics& graphics)
{
	Matrix3D rotation = Rotate(angle);
	Matrix3D translation = Translate(position.x, position.y);
	Matrix3D scaling = Scale(scale, scale);
	Matrix3D transform = translation * rotation * scaling;
	for(int i=0; i<numPlanetPoints; i++)
	{
		if(i+1 < numPlanetPoints)
		{
			Vector2D start = transform * planetPoints[i];
			Vector2D end = transform * planetPoints[i+1];
			graphics.DrawLine(start.x, start.y, end.x, end.y);
		}
		else
		{
			Vector2D start = transform * planetPoints[i];
			Vector2D end = transform * planetPoints[0];
			graphics.DrawLine(start.x, start.y, end.x, end.y);
		}
	}
}

void Planet::UpdatePlanet(float dt, Vector2D parentPos)
{
	angle += float(increment*dt);
	Vector2D relativePosition = Rotate(angle) * Vector2D(orbitDistance,0);
	parentPosition = Vector2D(parentPos.x, parentPos.y); 
	position = parentPosition + relativePosition;
}