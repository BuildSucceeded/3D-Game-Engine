#pragma once
#include "resource.h"
#include "framework.h"
#include "Point3D.h"

class Triangle
{
public:
	Triangle(Point3D p0, Point3D p1, Point3D p2, D2D1::ColorF::Enum c);

	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget, Point3D position, Point3D rotation);

	Point3D points[3];

	D2D1::ColorF::Enum color;

private:
	ID2D1SolidColorBrush* m_pColorBrush;
};