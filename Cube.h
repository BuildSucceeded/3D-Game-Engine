#pragma once
#include "resource.h"
#include "framework.h"
#include "EngineBase.h"
#include "GameObjectBase.h"
#include "Point3D.h"

class Cube : public GameObjectBase
{
public:
	Cube(Point3D pos);

	void Logic(double elapsedTime) override;
	
};

