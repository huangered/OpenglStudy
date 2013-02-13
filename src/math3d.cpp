#include "stdafx.h"
#include "math3d.h"

void LoadIdentity44(Matrix44f m)
{
	#define M(row,col)  m[col*4+row]
	M(0,0) = 1.0f;
	M(0,1) = 0.0f;
	M(0,2) = 0.0f;
	M(0,3) = 0.0f;

	M(1,0) = 0.0f;
	M(1,1) = 1.0f;
	M(1,2) = 0.0f;
	M(1,3) = 0.0f;

	M(2,0) = 0.0f;
	M(2,1) = 0.0f;
	M(2,2) = 1.0f;
	M(2,3) = 0.0f;

	M(3,0) = 0.0f;
	M(3,1) = 0.0f;
	M(3,2) = 0.0f;
	M(3,3) = 1.0f;
	#undef M
}


void CrossProduct(Vector3f result, const Vector3f u, const Vector3f v)
{
	result[0] =  u[1] * v[2] - v[1] * u[2];
	result[1] = -u[0] * v[2] + v[0] * u[2];
	result[2] =  u[0] * v[1] - v[0] * u[1];
}

void RotationMatrix44(Matrix44f m, float angle, float x, float y, float z)
{
	float mag, s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = float(sin(angle));
	c = float(cos(angle));

	mag = float(sqrt( x*x + y*y + z*z ));

	// Identity matrix
	if (mag == 0.0f) {
		LoadIdentity44(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

    #define M(row,col)  m[col*4+row]

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;

	M(0,0) = (one_c * xx) + c;
	M(0,1) = (one_c * xy) - zs;
	M(0,2) = (one_c * zx) + ys;
	M(0,3) = 0.0f;

	M(1,0) = (one_c * xy) + zs;
	M(1,1) = (one_c * yy) + c;
	M(1,2) = (one_c * yz) - xs;
	M(1,3) = 0.0f;

	M(2,0) = (one_c * zx) - ys;
	M(2,1) = (one_c * yz) + xs;
	M(2,2) = (one_c * zz) + c;
	M(2,3) = 0.0f;

	M(3,0) = 0.0f;
	M(3,1) = 0.0f;
	M(3,2) = 0.0f;
	M(3,3) = 1.0f;

    #undef M
}

