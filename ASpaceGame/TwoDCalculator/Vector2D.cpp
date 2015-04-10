#include <cmath>

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

float length(Vector2D vector)
	{
		return (sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
	}

float lengthSquared(Vector2D vector)
	{
		return (pow(vector.x,2) + pow(vector.y, 2));
	}

Vector2D normalized(Vector2D normal){
	Vector2D result;
	if(normal.x != 0)
	{
		result.x = normal.x * (1/length(normal));
	}
	if(normal.y != 0)
	{
		result.y = normal.y * (1/length(normal));
	}
	return result;
}

Vector2D operator+(const Vector2D& left, const Vector2D& right)
		{
			return Vector2D(left.x + right.x, left.y + right.y);
		}

Vector2D operator-(const Vector2D& left, const Vector2D& right)
		{
			return Vector2D(left.x - right.x, left.y - right.y);
		}

Vector2D operator*(const Vector2D& left, float scalar)
		{
			return Vector2D(scalar * left.x, scalar * left.y);
		}

Vector2D lerp(Vector2D a, Vector2D b, float beta)
{
	return Vector2D((1-beta)*a.x + beta*b.x, (1-beta)*a.y + beta*b.y);
}

float operator*(const Vector2D& left,const Vector2D& right)
{
	float scalar = left.x * right.x + left.y * right.y;
	return scalar;
}

float dotProduct(Vector2D one, Vector2D two)
{
	return one * two;
}

Vector2D projectOnto(Vector2D onto, float scalar)
{
	Vector2D result;
	if(lengthSquared(onto) != 0){
		result = Vector2D((onto.x/lengthSquared(onto)*scalar), (onto.y/lengthSquared(onto)*scalar));
	}
	return result;
}