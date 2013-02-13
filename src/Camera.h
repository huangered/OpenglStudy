/* The camera.cpp
 * implementation of the camera class
 * code by Huang yi.
 */
#ifndef _Camera_
#define _Camera_

#include <GL\glew.h>
#include <GL\glut.h>
#include "math3d.h"
class Camera
{
protected:
	Vector3f vOrigin;
	Vector3f vForward;
	Vector3f vUp;

public:
	Camera(void);
	~Camera(void);

	// Move along axis
	void MoveForward(float fDelta);
	void MoveUp(float fDelta);
	void MoveRight(float fDelta);

	// rotate 
	void RotateLocalX(float fAngle);
	void RotateLocalY(float fAngle);
	void RotateLocalZ(float fAngle);
	
	void ApplyCameraTransform();
	void GetCameraOrientation(Matrix44f m);		

	void show();
};

#endif // !_Camera_