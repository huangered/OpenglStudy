/* The abstract base class for camera and items
 * 	code by Huang yi
 */

#ifndef _glObject_
#define _glObject_
#include <GL\glew.h>
#include <GL\glut.h>
#include "math3d.h"	
class glObject
{
protected:
	Vector3f vOrigin;
	Vector3f vForward;
	Vector3f vUp;
public:
	glObject(void){}
	virtual ~glObject(void){};
	// Set Origin Location
	virtual void SetOrigin(const Vector3f vPoint)=0;
	virtual void SetOrigin(float x, float y, float z)=0;
	virtual float GetOriginX(void)=0;
	virtual float GetOriginY(void)=0;
	virtual float GetOriginZ(void)=0;
	
	// Move along axis
	virtual void MoveForward(float fDelta)=0;
	virtual void MoveUp(float fDelta)=0;
	virtual void MoveRight(float fDelta)=0;

	// rotate camera
	virtual void RotateLocalX(float fAngle)=0;
	virtual void RotateLocalY(float fAngle)=0;
	virtual void RotateLocalZ(float fAngle)=0;
	
	virtual void show()=0;
};
#endif // !_glObject_