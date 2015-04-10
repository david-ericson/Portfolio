#ifndef MATRIX3D
#define MATRIX3D
#include "Vector3D.h"
#include "Vector2D.h"
#include <cmath>


struct Matrix3D
{
	float m[3][3];
	Matrix3D() 
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(i == j)
					m[i][j] = 1;
				else
					m[i][j] = 0;
			}
		}
	}
	Matrix3D(Vector3D a, Vector3D b, Vector3D c)
	{
		Vector3D vecs[3] = {a,b,c};
		for(int i=0; i<3; i++)
		{
				m[0][i] = vecs[i].x;
				m[1][i] = vecs[i].y;
				m[2][i] = vecs[i].z;
		}
	}
	operator const float*() const
	{
		return &m[0][0];
	}
};

inline Vector2D operator*(const Matrix3D& m, const Vector2D& v)
{
	Vector2D result;
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2];
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2];
	return result;
}

inline Vector3D operator*(const Matrix3D& m, const Vector3D& v)
{
	Vector3D result;
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
	return result;
}

inline Matrix3D operator*(const Matrix3D& m, const Matrix3D& m2)
{
	return Matrix3D (
	Vector3D(
		m.m[0][0] * m2.m[0][0] + m.m[0][1] * m2.m[1][0] + m.m[0][2]* m2.m[2][0],
		m.m[1][0] * m2.m[0][0] + m.m[1][1] * m2.m[1][0] + m.m[1][2]* m2.m[2][0],
		m.m[2][0] * m2.m[0][0] + m.m[2][1] * m2.m[1][0] + m.m[2][2]* m2.m[2][0]),

	Vector3D(
		m.m[0][0] * m2.m[0][1] + m.m[0][1] * m2.m[1][1] + m.m[0][2] * m2.m[2][1],
		m.m[1][0] * m2.m[0][1] + m.m[1][1] * m2.m[1][1] + m.m[1][2] * m2.m[2][1],
		m.m[2][0] * m2.m[0][1] + m.m[2][1] * m2.m[1][1] + m.m[2][2] * m2.m[2][1]),

	Vector3D(
		m.m[0][0] * m2.m[0][2] + m.m[0][1] * m2.m[1][2] + m.m[0][2] * m2.m[2][2],
		m.m[1][0] * m2.m[0][2] + m.m[1][1] * m2.m[1][2] + m.m[1][2] * m2.m[2][2],
		m.m[2][0] * m2.m[0][2] + m.m[2][1] * m2.m[1][2] + m.m[2][2] * m2.m[2][2]));
}

inline Matrix3D Scale(float sx, float sy)
{
	return Matrix3D(
		Vector3D(sx, 0, 0), 
		Vector3D(0, sy, 0), 
		Vector3D(0, 0, 1));
}

inline Matrix3D Rotate(float angle)
{
	Matrix3D result;
	float c = cos(angle);
	float s = sin(angle);
	result = Matrix3D(
		Vector3D(c, s, 0), 
		Vector3D(-s, c, 0), 
		Vector3D(0, 0, 1));
	return result;
}

inline Matrix3D Translate (float tx, float ty)
{
	Matrix3D result;
	result.m[0][2] = tx;
	result.m[1][2] = ty;
	return result;
}

#endif