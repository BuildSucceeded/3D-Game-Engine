#pragma once
#include "resource.h"
#include "framework.h"
#include "EngineBase.h"
#include "GameObjectBase.h"

class Cube : public GameObjectBase
{
public:
	Cube();

	void Logic(double elapsedTime) override;
	
};

