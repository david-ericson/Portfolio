#include "PathedObject.h"

PathedObject::PathedObject() : GameObject(shipLinesCount, enemyShip)
{
	beta, startingLine = 0;
	path = serpentine;
	numPathLines = pathLinesCount;
	position = serpentine[0];
}

void PathedObject::followPath(float dt)
{
	velocity = (500*dt, 500*dt);
	if(startingLine+1<numPathLines)
	{
		position = lerp(path[startingLine], path[startingLine + 1], beta);
		beta += (1/(length(path[startingLine+1]-path[startingLine])/length(velocity)));
	}
	else
	{
		position = lerp(path[startingLine], path[0], beta);
		beta += (1/(length(path[0]-path[startingLine])/length(velocity)));
	}
	if(beta >= 1)
	{
		if(startingLine +1 < numPathLines)
			startingLine++;
		else
			startingLine = 0;
		position = path[startingLine];
		beta = 0;
	}
}