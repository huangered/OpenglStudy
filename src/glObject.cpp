#include "stdafx.h"
#include "glObject.h"

glObject::glObject(void)
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


glObject::~glObject(void)
{
	printf("object is dead.");
}


void glObject::SetOrigin(const Vector3f vPoint)
{
	CopyVector3(vOrigin,vPoint);
}

void glObject::SetOrigin(float x, float y, float z)
{
	vOrigin[0] = x;
	vOrigin[1] = y;
	vOrigin[2] = z;
}

float glObject::GetOriginX(void)
{
	return vOrigin[0]; 
}

float glObject::GetOriginY(void) 
{
	return vOrigin[1]; 
}

float glObject::GetOriginZ(void)
{
	return vOrigin[2];
}

void glObject::MoveForward(float fDelta)
{		
	vOrigin[0] += vForward[0] * fDelta;
	vOrigin[1] += vForward[1] * fDelta;
	vOrigin[2] += vForward[2] * fDelta;
}

void glObject::MoveUp(float fDelta)
{
	vOrigin[0] += vUp[0] * fDelta;
	vOrigin[1] += vUp[1] * fDelta;
	vOrigin[2] += vUp[2] * fDelta;
}

void glObject::MoveRight(float fDelta)
{
	Vector3f vCross;
	CrossProduct(vCross,vUp,vForward);
	
	vOrigin[0] += vCross[0] * fDelta;
	vOrigin[1] += vCross[1] * fDelta;
	vOrigin[2] += vCross[2] * fDelta;
}

void glObject::RotateLocalX(float fAngle)
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

void glObject::RotateLocalY(float fAngle)
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
		
void glObject::RotateLocalZ(float fAngle)
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

void glObject::ApplyActorTransform()
{
	Matrix44f rotMat;

	GetMatrix(rotMat, vOrigin, vUp, vForward);

	// apply rotation to the current matrix
	glMultMatrixf(rotMat);
}

void glObject::draw()
{
	glBegin(GL_LINES);
		glColor3ub(128,0,128);
		glVertex3f(0,-10,0);
		glVertex3f(0,10,0);
		glColor3ub(255,255,255);
	glEnd();
	//glutSolidCube(1);
}
void glObject::show()
{
	printf("obj:  Origin :=%5.3f    ;%5.3f    ;%5.3f\n",vOrigin[0],vOrigin[1],vOrigin[2]);
	printf("      Forward:=%5.3f    ;%5.3f    ;%5.3f\n",vForward[0],vForward[1],vForward[2]);
	printf("      Up     :=%5.3f    ;%5.3f    ;%5.3f\n",vUp[0],vUp[1],vUp[2]);
}