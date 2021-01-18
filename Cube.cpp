#include "Settings.h"
#include "Point3D.h"
#include "Cube.h"
#include "Engine.h"

Cube::Cube()
{
	IWICBitmap* textureBMP = engine->LoadImageInWIC(L"crate.png");
	Texture* texture = new Texture(textureBMP);

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
	triangles.push_back(new Triangle(Point3D::Create(-200, -200, -200, 0, 0), Point3D::Create(-200, 200, -200, 0, 1), Point3D::Create(200, -200, -200, 1, 0), texture));
	triangles.push_back(new Triangle(Point3D::Create(-200, 200, -200, 0, 1), Point3D::Create(200, 200, -200, 1, 1), Point3D::Create(200, -200, -200, 1, 0), texture));
	// back
	triangles.push_back(new Triangle(Point3D::Create(200, -200, 200, 1, 0), Point3D::Create(-200, 200, 200, 0, 1), Point3D::Create(-200, -200, 200, 0, 0), texture));
	triangles.push_back(new Triangle(Point3D::Create(200, -200, 200, 1, 0), Point3D::Create(200, 200, 200, 1, 1), Point3D::Create(-200, 200, 200, 0, 1), texture));
	// left
	triangles.push_back(new Triangle(Point3D::Create(-200, -200, 200, 0, 1), Point3D::Create(-200, -200, -200, 0, 0), Point3D::Create(200, -200, 200, 1, 1), texture));
	triangles.push_back(new Triangle(Point3D::Create(-200, -200, -200, 0, 0), Point3D::Create(200, -200, -200, 1, 0), Point3D::Create(200, -200, 200, 1, 1), texture));
	// right
	triangles.push_back(new Triangle(Point3D::Create(-200, 200, -200, 0, 0), Point3D::Create(200, 200, 200, 1, 1), Point3D::Create(200, 200, -200, 1, 0), texture));
	triangles.push_back(new Triangle(Point3D::Create(-200, 200, -200, 0, 0), Point3D::Create(-200, 200, 200, 0, 1), Point3D::Create(200, 200, 200, 1, 1), texture));
	// top
	triangles.push_back(new Triangle(Point3D::Create(-200, -200, 200, 0, 1), Point3D::Create(-200, 200, -200, 1, 0), Point3D::Create(-200, -200, -200, 0, 0), texture));
	triangles.push_back(new Triangle(Point3D::Create(-200, -200, 200, 0, 1), Point3D::Create(-200, 200, 200, 1, 1), Point3D::Create(-200, 200, -200,1, 0), texture));
	// bottom
	triangles.push_back(new Triangle(Point3D::Create(200, -200, -200, 0, 0), Point3D::Create(200, 200, -200, 1, 0), Point3D::Create(200, -200, 200, 0, 1), texture));
	triangles.push_back(new Triangle(Point3D::Create(200, -200, 200, 0, 1), Point3D::Create(200, 200, -200, 1, 0), Point3D::Create(200, 200, 200, 1, 1), texture));
	
}

void Cube::Logic(double elapsedTime)
{
	rotation.y += 1 * elapsedTime;
}
