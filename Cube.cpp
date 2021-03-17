#include "Settings.h"
#include "Point3D.h"
#include "Cube.h"
#include "Engine.h"

Cube::Cube(Point3D pos)
{
	IWICBitmap* textureBMP = engine->LoadImageInWIC(L"crate.png");
	Texture* texture = new Texture(textureBMP);

	position = pos;
	rotation = Point3D::Create(0, 0, 0);

	// front
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, -1000, 0, 0), Point3D::Create(-1000, 1000, -1000, 0, 1), Point3D::Create(1000, -1000, -1000, 1, 0), texture, ColorUnion::Create(0)));
	triangles.push_back(new Triangle(Point3D::Create(-1000, 1000, -1000, 0, 1), Point3D::Create(1000, 1000, -1000, 1, 1), Point3D::Create(1000, -1000, -1000, 1, 0), texture, ColorUnion::Create(0)));
	// back
	triangles.push_back(new Triangle(Point3D::Create(1000, -1000, 1000, 1, 0), Point3D::Create(-1000, 1000, 1000, 0, 1), Point3D::Create(-1000, -1000, 1000, 0, 0), texture, ColorUnion::Create(0)));
	triangles.push_back(new Triangle(Point3D::Create(1000, -1000, 1000, 1, 0), Point3D::Create(1000, 1000, 1000, 1, 1), Point3D::Create(-1000, 1000, 1000, 0, 1), texture, ColorUnion::Create(0)));
	// left
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, 1000, 0, 1), Point3D::Create(-1000, -1000, -1000, 0, 0), Point3D::Create(1000, -1000, 1000, 1, 1), texture, ColorUnion::Create(0)));
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, -1000, 0, 0), Point3D::Create(1000, -1000, -1000, 1, 0), Point3D::Create(1000, -1000, 1000, 1, 1), texture, ColorUnion::Create(0)));
	// right
	triangles.push_back(new Triangle(Point3D::Create(-1000, 1000, -1000, 0, 0), Point3D::Create(1000, 1000, 1000, 1, 1), Point3D::Create(1000, 1000, -1000, 1, 0), texture, ColorUnion::Create(0)));
	triangles.push_back(new Triangle(Point3D::Create(-1000, 1000, -1000, 0, 0), Point3D::Create(-1000, 1000, 1000, 0, 1), Point3D::Create(1000, 1000, 1000, 1, 1), texture, ColorUnion::Create(0)));
	// top
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, 1000, 0, 1), Point3D::Create(-1000, 1000, -1000, 1, 0), Point3D::Create(-1000, -1000, -1000, 0, 0), texture, ColorUnion::Create(0)));
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, 1000, 0, 1), Point3D::Create(-1000, 1000, 1000, 1, 1), Point3D::Create(-1000, 1000, -1000,1, 0), texture, ColorUnion::Create(0)));
	// bottom
	triangles.push_back(new Triangle(Point3D::Create(1000, -1000, -1000, 0, 0), Point3D::Create(1000, 1000, -1000, 1, 0), Point3D::Create(1000, -1000, 1000, 0, 1), texture, ColorUnion::Create(0)));
	triangles.push_back(new Triangle(Point3D::Create(1000, -1000, 1000, 0, 1), Point3D::Create(1000, 1000, -1000, 1, 0), Point3D::Create(1000, 1000, 1000, 1, 1), texture, ColorUnion::Create(0)));
	
}

void Cube::Logic(double elapsedTime)
{
	rotation.y += 1 * elapsedTime;
}
