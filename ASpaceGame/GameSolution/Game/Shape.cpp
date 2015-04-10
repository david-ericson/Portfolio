#include "Shape.h"


Shape::Shape(int lines, Vector2D* pointer)
	{
		numLines = lines;
		points = pointer;
	}

void Shape::Draw(Core::Graphics& graphics, Vector2D position)
{
	for(int i=0; i<numLines; i++)
	{
		if((i+1) < numLines)
		{
		graphics.DrawLine(position.x + points[i].x,position.y + points[i].y,
						position.x + points[i+1].x,position.y + points[i+1].y);
		}
		else
		{
			graphics.DrawLine(position.x + points[i].x,position.y + points[i].y,
				position.x + points[0].x,position.y +points[0].y);
		}
	}
}

Vector2D Shape::getLargestValues()
{
	Vector2D largestValues;
	for(int i=0; i<numLines; i++)
	{
		if(largestValues.x < points[i].x)
			largestValues.x = points[i].x;
		if(largestValues.y < points[i].y)
			largestValues.y = points[i].y;
	}
	return largestValues;
}

Vector2D Shape::getSmallestValues()
{
	Vector2D smallestValues;
	for(int i=0; i<numLines; i++)
	{
		if(smallestValues.x > points[i].x)
			smallestValues.x = points[i].x;
		if(smallestValues.y > points[i].y)
			smallestValues.y = points[i].y;
	}
	return smallestValues;
}