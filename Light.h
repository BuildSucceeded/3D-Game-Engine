#pragma once

#include "Point3D.h"
#include "ColorUnion.h"

enum LightType { ambiental, directional, fixed };

class Light
{
public:
	Light(LightType lightType, Point3D position, Point3D direction, ColorUnion color);
	Light(LightType lightType, Point3D position, Point3D direction, ColorUnion color, double length);

	LightType GetLightType();
	Point3D GetPosition();
	Point3D GetDirection();
	ColorUnion GetColor();
	double GetLength();

private:
	Point3D position;
	Point3D direction;
	ColorUnion color;
	double length;

	LightType lightType;
};