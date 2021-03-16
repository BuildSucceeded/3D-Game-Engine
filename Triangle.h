#pragma once
#include "resource.h"
#include "framework.h"
#include "Point3D.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"

class Triangle
{
public:
	Triangle(Point3D p0, Point3D p1, Point3D p2, Texture* t, ColorUnion light);

	void CalculateWorldPoints(Point3D position, Point3D rotation);
	void ApplyLight(Light* light);
	void CalculateCameraView(Camera* camera);
	void CalculateDrawPoints();
	void Draw(int *renderBuffer);

	static bool SortOrder(Triangle* triangle1, Triangle* triangle2);

	double GetNormalZ();
	Point3D* GetCameraPoints();
	Point3D* GetDrawPoints();

	std::list<Triangle*> GetZClippedTriangles();
	std::list<Triangle*> GetClippedTriangles();

private:

	Texture* texture;

	ColorUnion lightAmount;

	Point3D points[3];
	Point3D worldPoints[3];
	Point3D cameraPoints[3];
	Point3D drawPoints[3];
	double averageZ;
	double normalZ;
};