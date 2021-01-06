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
	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget) override;

private:

	Point3D points[8];

	ID2D1SolidColorBrush* m_pWhiteBrush;
	
};

