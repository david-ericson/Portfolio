#ifndef VECTOR3D
#define VECTOR3D

struct Vector3D
{
	float x, y, z;
	Vector3D( float x =0, float y=0, float z=0) : x(x), y(y), z(z) {}
	operator const float*() const
	{
		return &x;
	}
};

#endif