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

	noTriangles = 12;
	// front
	triangles[0] = new Triangle(point0, point1, point3, D2D1::ColorF::Red);
	triangles[1] = new Triangle(point1, point2, point3, D2D1::ColorF::Red);
	// back
	triangles[2] = new Triangle(point7, point5, point4, D2D1::ColorF::Red);
	triangles[3] = new Triangle(point7, point6, point5, D2D1::ColorF::Red);
	// left
	triangles[4] = new Triangle(point4, point0, point7, D2D1::ColorF::Green);
	triangles[5] = new Triangle(point0, point3, point7, D2D1::ColorF::Green);
	// right
	triangles[6] = new Triangle(point1, point6, point2, D2D1::ColorF::Green);
	triangles[7] = new Triangle(point1, point5, point6, D2D1::ColorF::Green);
	// top
	triangles[8] = new Triangle(point4, point1, point0, D2D1::ColorF::Blue);
	triangles[9] = new Triangle(point4, point5, point1, D2D1::ColorF::Blue);
	// bottom
	triangles[10] = new Triangle(point3, point2, point7, D2D1::ColorF::Blue);
	triangles[11] = new Triangle(point7, point2, point6, D2D1::ColorF::Blue);
}

void Cube::Logic(double elapsedTime)
{
	rotation.y += 1 * elapsedTime;
}
