#pragma once
#include "globject.h"
class glCommonObject :
	public glObject
{
public:
	glCommonObject(void);
	~glCommonObject(void);

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
	
	virtual void show();

	void ApplyActorTransform();
	virtual void draw();
};

