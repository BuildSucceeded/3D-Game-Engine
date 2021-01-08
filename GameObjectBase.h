#pragma once

class EngineBase;

#include <vector>
#include "resource.h"
#include "EngineBase.h"
#include "Point3D.h"
#include "Triangle.h"

class GameObjectBase
{
public:

	virtual void Logic(double elapsedTime) {}

	Point3D GetPosition();
	Point3D GetRotation();

	EngineBase* engine;

	std::vector<Triangle*> triangles;
	
protected:

	Point3D position;
	Point3D speed;
	Point3D rotation;
};

