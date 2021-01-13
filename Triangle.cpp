#include "Settings.h"
#include "Point3D.h"
#include "Triangle.h"
#include "EngineBase.h"

Triangle::Triangle(Point3D p0, Point3D p1, Point3D p2, D2D1::ColorF::Enum c)
{
	points[0] = p0;
	points[1] = p1;
	points[2] = p2;
	color = c;
}

void Triangle::CalculateWorldPoints(Point3D position, Point3D rotation)
{
	// Rotate
	for (int i = 0; i < 3; i++)
		worldPoints[i] = EngineBase::Rotate(points[i], rotation);

	// Translate
	for (int i = 0; i < 3; i++)
		worldPoints[i] = EngineBase::Translate(worldPoints[i], position);

	// Average Z (for sorting triangles)
	averageZ = (worldPoints[0].z + worldPoints[1].z + worldPoints[2].z) / 3.0;
}

void Triangle::CalculateDrawPoints()
{
	// Apply perspective
	for (int i = 0; i < 3; i++)
		drawPoints[i] = EngineBase::ApplyPerspective(worldPoints[i]);

	// Center screen
	for (int i = 0; i < 3; i++)
		drawPoints[i] = EngineBase::CenterScreen(drawPoints[i]);

	// Normal Z -  is the triangle facing us or the other way
	normalZ = (drawPoints[1].x - drawPoints[0].x) * (drawPoints[2].y - drawPoints[0].y) - (drawPoints[1].y - drawPoints[0].y) * (drawPoints[2].x - drawPoints[0].x);
}

void Triangle::Draw(int* renderBuffer)
{
	
	Point3D aux;
	if (drawPoints[0].y > drawPoints[1].y) {
		aux = drawPoints[0];
		drawPoints[0] = drawPoints[1];
		drawPoints[1] = aux;
	}
	if (drawPoints[0].y > drawPoints[2].y) {
		aux = drawPoints[0];
		drawPoints[0] = drawPoints[2];
		drawPoints[2] = aux;
	}
	if (drawPoints[1].y > drawPoints[2].y) {
		aux = drawPoints[1];
		drawPoints[1] = drawPoints[2];
		drawPoints[2] = aux;
	}

	if (drawPoints[0].y < drawPoints[1].y) {
		double slope1 = (drawPoints[1].x - drawPoints[0].x) / (drawPoints[1].y - drawPoints[0].y);
		double slope2 = (drawPoints[2].x - drawPoints[0].x) / (drawPoints[2].y - drawPoints[0].y);
		for (int i = 0; i <= drawPoints[1].y - drawPoints[0].y; i++) {
			int x1 = drawPoints[0].x + i * slope1;
			int x2 = drawPoints[0].x + i * slope2;
			int y = drawPoints[0].y + i;

			if (x1 > x2) {
				int aux = x1;
				x1 = x2;
				x2 = aux;
			}
			for (int j = x1; j <= x2; j++) {
				renderBuffer[RESOLUTION_X * y + j] = color;
			}
		}
	}
	if (drawPoints[1].y < drawPoints[2].y) {
		double slope1 = (drawPoints[2].x - drawPoints[1].x) / (drawPoints[2].y - drawPoints[1].y);
		double slope2 = (drawPoints[2].x - drawPoints[0].x) / (drawPoints[2].y - drawPoints[0].y);
		double sx = drawPoints[2].x - (drawPoints[2].y - drawPoints[1].y) * slope2;
		for (int i = 0; i <= drawPoints[2].y - drawPoints[1].y; i++) {
			double x1 = drawPoints[1].x + i * slope1;
			double x2 = sx + i * slope2;
			int y = drawPoints[1].y + i;

			if (x1 > x2) {
				int aux = x1;
				x1 = x2;
				x2 = aux;
			}
			for (int j = x1; j <= x2; j++) {
				renderBuffer[RESOLUTION_X * y + j] = color;
			}
		}
	}
}

bool Triangle::SortOrder(Triangle* triangle1, Triangle* triangle2)
{
	return triangle1->averageZ > triangle2->averageZ;
}

double Triangle::GetNormalZ()
{
	return normalZ;
}