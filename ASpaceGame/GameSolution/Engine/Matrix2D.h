#ifndef MATRIX2D
#define MATRIX2D
#include "Vector2D.h"

struct Matrix2D
{
	Vector2D firstBasis;
	Vector2D secondBasis;
	Matrix2D(float a = 1, float b = 0, 
		float c = 0, float d = 1) : firstBasis(a, b), 
		secondBasis(c,d){}
	Matrix2D(Vector2D a, Vector2D b)
	{
		firstBasis = a;
		secondBasis = b;
	}
};

inline Matrix2D operator*(const Matrix2D& a, const Matrix2D& b)
{
	Matrix2D result;
	result.firstBasis.x = a.firstBasis.x * b.firstBasis.x + a.secondBasis.x * b.firstBasis.y;
	result.firstBasis.y = a.firstBasis.y * b.firstBasis.x + a.secondBasis.y * b.firstBasis.y;
	result.secondBasis.x = a.firstBasis.x * b.secondBasis.x + a.secondBasis.x * b.secondBasis.y;
	result.secondBasis.y = a.firstBasis.y * b.secondBasis.x + a.secondBasis.y * b.secondBasis.y;
	return result;
}


inline Vector2D operator*(const Matrix2D& matrix, const Vector2D& vector)
{
	return Vector2D
	(
		matrix.firstBasis.x * vector.x + matrix.secondBasis.x * vector.y,
		matrix.firstBasis.y * vector.x + matrix.secondBasis.y * vector.y
	);
}

inline Matrix2D Rotate2D(float angle)
{
	Matrix2D result;
	float c = cos(angle);
	float s = sin(angle);
	result = Matrix2D(
		Vector2D(c, s), 
		Vector2D(-s, c));
	return result;
}

#endif