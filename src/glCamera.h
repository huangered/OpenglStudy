/* The camera.cpp
 * implementation of the camera class
 * code by Huang yi.
 */
#ifndef _Camera_H_
#define _Camera_H_

#include "Common.h"
#include "glObjectBase.h"
#include "math3d.h"

class glCamera : public glObjectBase
{				 
public:
	glCamera(void);
	~glCamera(void);

	// Set Origin Location
	virtual void SetOrigin(const Vector3f vPoint);
	virtual void SetOrigin(float x, float y, float z);
	virtual float GetOriginX(void);
	virtual float GetOriginY(void);
	virtual float GetOriginZ(void);

	// Move along axis
	virtual void MoveForward(float fDelta);
	virtual void MoveUp(float fDelta);
	virtual void MoveRight(float fDelta);

	// rotate camera
	virtual void RotateLocalX(float fAngle);
	virtual void RotateLocalY(float fAngle);
	virtual void RotateLocalZ(float fAngle);
	
	void ApplyCameraTransform();
	void GetCameraOrientation(Matrix44f m);		

	virtual void show();
};

#endif // !_Camera_