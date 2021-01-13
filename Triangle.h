#pragma once
#include "resource.h"
#include "framework.h"
#include "Point3D.h"

class Triangle
{
public:
	Triangle(Point3D p0, Point3D p1, Point3D p2, D2D1::ColorF::Enum c);

	void CalculateWorldPoints(Point3D position, Point3D rotation);
	void CalculateDrawPoints();
	void Draw(int *renderBuffer);

	static bool SortOrder(Triangle* triangle1, Triangle* triangle2);

	double GetNormalZ();

private:

	D2D1::ColorF::Enum color;

	Point3D points[3];
	Point3D worldPoints[3];
	Point3D drawPoints[3];
	double averageZ;
	double normalZ;
};