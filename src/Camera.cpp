#include "stdafx.h"
#include "Camera.h"
#include <math.h>
Camera::Camera(void)
{
	// At origin
	vOrigin[0] = 0.0f;
	vOrigin[1] = 0.0f;
	vOrigin[2] = 0.0f;

	// Up is up (+Y)
	vUp[0] = 0.0f; 
	vUp[1] = 1.0f; 
	vUp[2] = 0.0f;

	// Forward is -Z (default OpenGL)
    vForward[0] = 0.0f; 
	vForward[1] = 0.0f; 
	vForward[2] = -1.0f;

}	 

Camera::~Camera(void)
{
	
}

void Camera::MoveForward(float fDelta)
{		
	vOrigin[0] += vForward[0] * fDelta;
	vOrigin[1] += vForward[1] * fDelta;
	vOrigin[2] += vForward[2] * fDelta;
}

void Camera::MoveUp(float fDelta)
{
	vOrigin[0] += vUp[0] * fDelta;
	vOrigin[1] += vUp[1] * fDelta;
	vOrigin[2] += vUp[2] * fDelta;
}

void Camera::MoveRight(float fDelta)
{
	Vector3f vCross;
	CrossProduct(vCross,vUp,vForward);
	
	vOrigin[0] += vCross[0] * fDelta;
	vOrigin[1] += vCross[1] * fDelta;
	vOrigin[2] += vCross[2] * fDelta;
}

void Camera::RotateLocalX(float fAngle)
{
	Matrix44f rotMat;
	Vector3f vCross;
	CrossProduct(vCross,vUp,vForward);
	RotationMatrix44(rotMat, fAngle,
						vCross[0], vCross[1], vCross[2]);
	Vector3f newVect;
	// Inline 3x3 matrix multiply for rotation only
	newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];	
	newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];	
	newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];	
	CopyVector3(vForward, newVect);

	// Update pointing up vector
	newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];	
	newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];	
	newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];	
	CopyVector3(vUp, newVect);
}

void Camera::RotateLocalY(float fAngle)
{
	Matrix44f rotMat;

	// Just Rotate around the up vector
	// Create a rotation matrix around my Up (Y) vector
	RotationMatrix44(rotMat, fAngle,
                    vUp[0], vUp[1], vUp[2]);

	Vector3f newVect;

	// Rotate forward pointing vector (inlined 3x3 transform)
	newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];	
	newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];	
	newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];	
	CopyVector3(vForward, newVect);
}
		
void Camera::RotateLocalZ(float fAngle)
{
	Matrix44f rotMat;

	// Only the up vector needs to be rotated
	RotationMatrix44(rotMat, fAngle,
					vForward[0], vForward[1], vForward[2]);

	Vector3f newVect;
	newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];	
	newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];	
	newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];	
	CopyVector3(vUp, newVect);
}

void Camera::ApplyCameraTransform()
{
	Matrix44f m;

	GetCameraOrientation(m);

	glMultMatrixf(m);

	glTranslatef(-vOrigin[0], -vOrigin[1], -vOrigin[2]);
}

void Camera::GetCameraOrientation(Matrix44f m)
{
	Vector3f x, z;

	// Make rotation matrix
	// Z vector is reversed
	z[0] = -vForward[0];
	z[1] = -vForward[1];
	z[2] = -vForward[2];

	// X vector = Y cross Z 
	CrossProduct(x, vUp, z);

	// Matrix has no translation information and is
	// transposed.... (rows instead of columns)
	#define M(row,col)  m[col*4+row]
	   M(0, 0) = x[0];
	   M(0, 1) = x[1];
	   M(0, 2) = x[2];
	   M(0, 3) = 0.0;
	   M(1, 0) = vUp[0];
	   M(1, 1) = vUp[1];
	   M(1, 2) = vUp[2];
	   M(1, 3) = 0.0;
	   M(2, 0) = z[0];
	   M(2, 1) = z[1];
	   M(2, 2) = z[2];
	   M(2, 3) = 0.0;
	   M(3, 0) = 0.0;
	   M(3, 1) = 0.0;
	   M(3, 2) = 0.0;
	   M(3, 3) = 1.0;
	#undef M 
}

void Camera::show()
{
	printf("Origin :=%5.3f    ;%5.3f    ;%5.3f\n",vOrigin[0],vOrigin[1],vOrigin[2]);
	printf("Forward:=%5.3f    ;%5.3f    ;%5.3f\n",vForward[0],vForward[1],vForward[2]);
	printf("Up     :=%5.3f    ;%5.3f    ;%5.3f\n",vUp[0],vUp[1],vUp[2]);

}