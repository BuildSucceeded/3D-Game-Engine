#include "Settings.h"
#include "Point3D.h"
#include "Cube.h"
#include "Engine.h"

Cube::Cube()
{
	IWICBitmap* textureBMP = engine->LoadImageInWIC(L"crate.png");
	Texture* texture = new Texture(textureBMP);

	position = Point3D::Create(0, 0, 4000);
	rotation = Point3D::Create(0, 0, 0);

	// front
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, -1000, 0, 0), Point3D::Create(-1000, 1000, -1000, 0, 1), Point3D::Create(1000, -1000, -1000, 1, 0), texture));
	triangles.push_back(new Triangle(Point3D::Create(-1000, 1000, -1000, 0, 1), Point3D::Create(1000, 1000, -1000, 1, 1), Point3D::Create(1000, -1000, -1000, 1, 0), texture));
	// back
	triangles.push_back(new Triangle(Point3D::Create(1000, -1000, 1000, 1, 0), Point3D::Create(-1000, 1000, 1000, 0, 1), Point3D::Create(-1000, -1000, 1000, 0, 0), texture));
	triangles.push_back(new Triangle(Point3D::Create(1000, -1000, 1000, 1, 0), Point3D::Create(1000, 1000, 1000, 1, 1), Point3D::Create(-1000, 1000, 1000, 0, 1), texture));
	// left
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, 1000, 0, 1), Point3D::Create(-1000, -1000, -1000, 0, 0), Point3D::Create(1000, -1000, 1000, 1, 1), texture));
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, -1000, 0, 0), Point3D::Create(1000, -1000, -1000, 1, 0), Point3D::Create(1000, -1000, 1000, 1, 1), texture));
	// right
	triangles.push_back(new Triangle(Point3D::Create(-1000, 1000, -1000, 0, 0), Point3D::Create(1000, 1000, 1000, 1, 1), Point3D::Create(1000, 1000, -1000, 1, 0), texture));
	triangles.push_back(new Triangle(Point3D::Create(-1000, 1000, -1000, 0, 0), Point3D::Create(-1000, 1000, 1000, 0, 1), Point3D::Create(1000, 1000, 1000, 1, 1), texture));
	// top
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, 1000, 0, 1), Point3D::Create(-1000, 1000, -1000, 1, 0), Point3D::Create(-1000, -1000, -1000, 0, 0), texture));
	triangles.push_back(new Triangle(Point3D::Create(-1000, -1000, 1000, 0, 1), Point3D::Create(-1000, 1000, 1000, 1, 1), Point3D::Create(-1000, 1000, -1000,1, 0), texture));
	// bottom
	triangles.push_back(new Triangle(Point3D::Create(1000, -1000, -1000, 0, 0), Point3D::Create(1000, 1000, -1000, 1, 0), Point3D::Create(1000, -1000, 1000, 0, 1), texture));
	triangles.push_back(new Triangle(Point3D::Create(1000, -1000, 1000, 0, 1), Point3D::Create(1000, 1000, -1000, 1, 0), Point3D::Create(1000, 1000, 1000, 1, 1), texture));
	
}

void Cube::Logic(double elapsedTime)
{
	//rotation.y += 1 * elapsedTime;
}
