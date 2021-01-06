#pragma once

class EngineBase;

#include "resource.h"
#include "EngineBase.h"
#include "Point3D.h"

class GameObjectBase
{
public:

	virtual void Logic(double elapsedTime) {}

	virtual void Draw(ID2D1HwndRenderTarget* m_pRenderTarget) {}

	Point3D GetPosition();

	EngineBase* engine;
	
protected:

	Point3D position;
	Point3D speed;
	Point3D rotation;
};

