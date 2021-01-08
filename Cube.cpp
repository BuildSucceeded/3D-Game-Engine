#include "Settings.h"
#include "Point3D.h"
#include "Cube.h"
#include "Engine.h"

Cube::Cube()
{
	position = Point3D::Create(0, 0, 400);
	rotation = Point3D::Create(0, 0, 0);

	Point3D point0 = Point3D::Create(-200, -200, -200);
	Point3D point1 = Point3D::Create(-200, 200, -200);
	Point3D point2 = Point3D::Create(200, 200, -200);
	Point3D point3 = Point3D::Create(200, -200, -200);
	Point3D point4 = Point3D::Create(-200, -200, 200);
	Point3D point5 = Point3D::Create(-200, 200, 200);
	Point3D point6 = Point3D::Create(200, 200, 200);
	Point3D point7 = Point3D::Create(200, -200, 200);

	// front
	triangles.push_back(new Triangle(point0, point1, point3, D2D1::ColorF::Red));
	triangles.push_back(new Triangle(point1, point2, point3, D2D1::ColorF::Red));
	// back
	triangles.push_back(new Triangle(point7, point5, point4, D2D1::ColorF::Orange));
	triangles.push_back(new Triangle(point7, point6, point5, D2D1::ColorF::Orange));
	// left
	triangles.push_back(new Triangle(point4, point0, point7, D2D1::ColorF::Green));
	triangles.push_back(new Triangle(point0, point3, point7, D2D1::ColorF::Green));
	// right
	triangles.push_back(new Triangle(point1, point6, point2, D2D1::ColorF::Yellow));
	triangles.push_back(new Triangle(point1, point5, point6, D2D1::ColorF::Yellow));
	// top
	triangles.push_back(new Triangle(point4, point1, point0, D2D1::ColorF::Blue));
	triangles.push_back(new Triangle(point4, point5, point1, D2D1::ColorF::Blue));
	// bottom
	triangles.push_back(new Triangle(point3, point2, point7, D2D1::ColorF::Magenta));
	triangles.push_back(new Triangle(point7, point2, point6, D2D1::ColorF::Magenta));
}

void Cube::Logic(double elapsedTime)
{
	rotation.y += 0.1 * elapsedTime;
}
