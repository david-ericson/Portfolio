#ifndef CALLBACK
#define CALLBACK

#include "Matrix2D.h"
#include "Matrix3D.h"

Vector2D left;
Vector2D right;
Vector2D result;

Vector2D original;
Vector2D normal;
Vector2D cwPerpendicular;
Vector2D ccwPerpendicular;

Vector2D first;
Vector2D second;
Vector2D projection;
Vector2D rejection;

Vector2D a;
Vector2D b;
Vector2D aMinusb;
Vector2D aLerpPortion;
Vector2D bLerpPortion;
Vector2D lerpResult;

Vector2D result2;

Vector3D affineResults[5]; 

const float span = .3f;

// Vertices and lines:
Vector2D bottomLeft(-span, -span);
Vector2D topLeft(-span, span);
Vector2D topRight(span, span);
Vector2D bottomRight(span, -span);
Vector2D roofTop(0, span + .25f);

Vector2D lines[] = { 
	bottomLeft, topLeft,
	topLeft, topRight,
	topRight, bottomRight,
	bottomRight, bottomLeft,
	topLeft, roofTop,
	topRight, roofTop
};

int numLines = sizeof(lines) / (sizeof(*lines) * 2);

const int numMatrices = 10;
Matrix3D matrices[numMatrices];
Matrix3D currentTransform;

#endif