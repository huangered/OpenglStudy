/* The camera.cpp
 * implementation of the camera class
 * code by Huang yi.
 */
#ifndef _Camera_
#define _Camera_ 
#include "glObject.h"
class glCamera : public glObject
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