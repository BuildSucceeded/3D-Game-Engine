#pragma once

#include "resource.h"
#include "Point3D.h"
#include "EngineBase.h"
#include "GameObjectBase.h"

class EngineBase
{
public:

	EngineBase();
	~EngineBase();

	HRESULT InitializeD2D(HWND m_hwnd);

	void MousePosition(int x, int y);

	virtual void KeyUp(WPARAM wParam);
	virtual void KeyDown(WPARAM wParam);
	virtual void MouseButtonUp(bool left, bool right);
	virtual void MouseButtonDown(bool left, bool right);

	void AddGameObject(GameObjectBase* gameObj);
	void RemoveGameObject(GameObjectBase* gameObj);

	virtual void Logic(double elapsedTime);
	HRESULT Draw();

	ID2D1Bitmap* LoadImage(LPCWSTR imageFile);

	double GetZ0();

	Point3D Translate(Point3D original, Point3D translation);
	Point3D Rotate(Point3D original, Point3D translation);
	Point3D ApplyPerspective(Point3D original);
	Point3D CenterScreen(Point3D original);

protected:

	Point3D mousePosition;

private:

	double Z0;

	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	GameObjectBase* objectList[1000];
	int noObjects = 0;
};

