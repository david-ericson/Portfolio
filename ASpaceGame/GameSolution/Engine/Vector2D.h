#ifndef VECTOR2D
#define VECTOR2D

struct Vector2D{
	float x;
	float y;
	Vector2D(float x = 0, float y = 0) : x(x), y(y) {}
	operator float*()
	{
		return &x;
	}

	Vector2D perpcw()
	{
		return Vector2D(y, -x);
	}

	Vector2D perpccw()
	{
		return Vector2D(-y, x);
	}
};

float length(Vector2D vector);

float lengthSquared(Vector2D vector);

Vector2D normalized(Vector2D normal);

Vector2D operator+(const Vector2D& left, const Vector2D& right);

Vector2D operator-(const Vector2D& left, const Vector2D& right);

Vector2D operator*(const Vector2D& left, float scalar);

Vector2D lerp(Vector2D a, Vector2D b, float beta);

float operator*(const Vector2D& left,const Vector2D& right);

float dotProduct(Vector2D one, Vector2D two);

Vector2D projectOnto(Vector2D onto, float scalar);

#endif
