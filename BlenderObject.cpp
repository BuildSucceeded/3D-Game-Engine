#include "Settings.h"
#include "Point3D.h"
#include "BlenderObject.h"
#include "Engine.h"

BlenderObject::BlenderObject(LPCWSTR objectFile, LPCWSTR textureFile, double scale)
{
	this->objectFile = objectFile;
	this->textureFile = textureFile;
	this->scale = scale;

	position = Point3D::Create(0, 2000, 6000);
	rotation = Point3D::Create(0, 0, 0);

}

void BlenderObject::Load()
{
	// Load texture
	IWICBitmap* textureBMP = engine->LoadImageInWIC(textureFile);
	texture = new Texture(textureBMP);

	// Load object
	std::ifstream myfile(objectFile);
	if (myfile.is_open())
	{
		std::string line;
		
		// Load vertices and texture points
		std::vector<Point3D> vertices;
		std::vector<Point3D> texturePoints;
		
		while (std::getline(myfile, line))
		{
			std::istringstream iss(line);
			std::string lineType;

			iss >> lineType;
			if (lineType == "v") // 3D point
			{
				double x, y, z;
				iss >> x >> y >> z;

				Point3D p = Point3D::Create(x, y, z);
				vertices.push_back(p);
			}
			else if (lineType == "vt") // Texture point
			{
				double u, v;
				iss >> u >> v;

				Point3D p = Point3D::Create(0, 0, 0, u, v);
				texturePoints.push_back(p);
			}
		}

		// Load triangles
		triangles.empty();

		myfile.clear();
		myfile.seekg(0);

		while (std::getline(myfile, line))
		{
			std::istringstream iss(line);
			std::string lineType;

			iss >> lineType;
			if (lineType == "f") // Triangle
			{
				int a, b, c;
				char s;

				iss >> a >> s >> b >> s >> c;
				Point3D p0 = Point3D::Create(vertices[a - 1].x * scale, -vertices[a - 1].y * scale, vertices[a - 1].z * scale, texturePoints[b - 1].u, texturePoints[b - 1].v);
				iss >> a >> s >> b >> s >> c;
				Point3D p1 = Point3D::Create(vertices[a - 1].x * scale, -vertices[a - 1].y * scale, vertices[a - 1].z * scale, texturePoints[b - 1].u, texturePoints[b - 1].v);
				iss >> a >> s >> b >> s >> c;
				Point3D p2 = Point3D::Create(vertices[a - 1].x * scale, -vertices[a - 1].y * scale, vertices[a - 1].z * scale, texturePoints[b - 1].u, texturePoints[b - 1].v);

				triangles.push_back(new Triangle(p0, p2, p1, texture, ColorUnion::Create(0)));

			}
		}
	}
}

void BlenderObject::Logic(double elapsedTime)
{
	rotation.y += 1 * elapsedTime;
}