#ifndef CALLBACK
#define CALLBACK

#include <glm/glm/glm.hpp>

glm::vec2 left;
glm::vec2 right;
glm::vec2 result;

glm::vec2 original;
glm::vec2 normal;
glm::vec2 cwPerpendicular;
glm::vec2 ccwPerpendicular;

glm::vec2 first;
glm::vec2 second;
glm::vec2 projection;
glm::vec2 rejection;

glm::vec2 a;
glm::vec2 b;
glm::vec2 aMinusb;
glm::vec2 aLerpPortion;
glm::vec2 bLerpPortion;
glm::vec2 lerpResult;

glm::vec2 result2;

glm::vec3 affineResults[5]; 

const float span = .3f;

// Vertices and lines:
glm::vec2 bottomLeft(-span, -span);
glm::vec2 topLeft(-span, span);
glm::vec2 topRight(span, span);
glm::vec2 bottomRight(span, -span);
glm::vec2 roofTop(0, span + .25f);

glm::vec2 lines[] = { 
	bottomLeft, topLeft,
	topLeft, topRight,
	topRight, bottomRight,
	bottomRight, bottomLeft,
	topLeft, roofTop,
	topRight, roofTop
};

int numLines = sizeof(lines) / (sizeof(*lines) * 2);

const int numMatrices = 10;
glm::mat3 matrices[numMatrices];
glm::mat3 currentTransform;

glm::mat4 fullTransform;
glm::mat4 matrices3D[numMatrices];

inline glm::mat3 Scale(float sx, float sy)
{
	return glm::mat3(
		glm::vec3(sx, 0, 0), 
		glm::vec3(0, sy, 0), 
		glm::vec3(0, 0, 1));
}

inline glm::mat3 Rotate(float angle)
{
	glm::mat3 result;
	float c = cos(angle);
	float s = sin(angle);
	result = glm::mat3(
		glm::vec3(c, s, 0), 
		glm::vec3(-s, c, 0), 
		glm::vec3(0, 0, 1));
	return result;
}

inline glm::mat3 Translate (float tx, float ty)
{
	glm::mat3 result;
	result[0][2] = tx;
	result[1][2] = ty;
	return result;
}

#endif