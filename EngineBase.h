#pragma once

#include <vector>
#include "resource.h"
#include "Settings.h"
#include "Point3D.h"
#include "EngineBase.h"
#include "GameObjectBase.h"
#include "Camera.h"
#include "Light.h"

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

	void AddLight(Light* light);
	void RemoveLight(Light* light);

	virtual void Logic(double elapsedTime);
	HRESULT Draw();

	ID2D1Bitmap* LoadImage(LPCWSTR imageFile);
	IWICBitmap* LoadImageInWIC(LPCWSTR imageFile);

	static double GetZ0();

	static Point3D CalculateNormal(Point3D p1, Point3D p2, Point3D p3);
	static double CalculateDotProduct(Point3D p1, Point3D p2);
	static Point3D Translate(Point3D original, Point3D translation);
	static Point3D Rotate(Point3D original, Point3D translation);
	static Point3D ApplyPerspective(Point3D original);
	static Point3D CenterScreen(Point3D original);

protected:

	Point3D mousePosition;

	Camera* camera;

private:

	void AntiAliasing();

	static double Z0;

	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	std::vector<GameObjectBase*> objectList;

	std::vector<Light*> lights;

	ID2D1Bitmap* pBitmap;
	

	int renderBuffer[RESOLUTION_X * RESOLUTION_Y];
	double zBuffer[RESOLUTION_X * RESOLUTION_Y];
};

