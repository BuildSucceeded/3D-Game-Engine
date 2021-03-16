#pragma once

#include "resource.h"
#include "framework.h"
#include "Point3D.h"

class Camera
{
public:
	Camera();
	Camera(Point3D position, Point3D rotation);

	void HandleKeyDown(WPARAM wParam);
	void HandleKeyUp(WPARAM wParam);

	void Logic(double elapsedTime);

	Point3D GetPosition();
	Point3D GetRotation();
	
private:
	Point3D position;
	Point3D rotation;

	bool leftPressed;
	bool rightPressed;
	bool wPressed;
	bool sPressed;
	bool aPressed;
	bool dPressed;
};