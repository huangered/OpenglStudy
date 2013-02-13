#pragma once

#include "stdafx.h"
#include <math.h>
#include <memory.h>
#include <GL\glew.h>
#include <GL\glut.h>

typedef float Vector2f[2];		// vector of two floats (x, y)
typedef float Vector3f[3];		// vector of three floats (x, y, z)
typedef float Vector4f[4];		// vector of four floats (x, y, z, w)
// 3x3 matrix - column major. X vector is 0, 1, 2, etc.
//		0	3	6	
//		1	4	7
//		2	5	8
typedef float Matrix33f[9];		// A 3 x 3 matrix, column major (floats) - OpenGL Style
// 4x4 matrix - column major. X vector is 0, 1, 2, etc.
//	0	4	8	12
//	1	5	9	13
//	2	6	10	14
//	3	7	11	15
typedef float Matrix44f[16];		// A 4 X 4 matrix, column major (floats) - OpenGL style
void LoadIdentity44(Matrix44f m);

////////////////////////////////////////////////////////////////////////////////
// Copy vector src into vector dst
inline void	CopyVector2(Vector2f dst, const Vector2f src) { memcpy(dst, src, sizeof(Vector2f)); }
inline void	CopyVector3(Vector3f dst, const Vector3f src) { memcpy(dst, src, sizeof(Vector3f)); }
inline void	CopyVector4(Vector4f dst, const Vector4f src) { memcpy(dst, src, sizeof(Vector4f)); }

//////////////////////////////////////////////////////////////////////////////////////
// Cross Product
// u x v = result
// We only need one version for floats, and one version for doubles. A 3 component
// vector fits in a 4 component vector. If  M3DVector4d or M3DVector4f are passed
// we will be OK because 4th component is not used.
void CrossProduct(Vector3f result, const Vector3f u, const Vector3f v);

///////////////////////////////////////////////////////////////////////////////
// Creates a 4x4 rotation matrix, takes radians NOT degrees
void RotationMatrix44(Matrix44f m, float angle, float x, float y, float z);
