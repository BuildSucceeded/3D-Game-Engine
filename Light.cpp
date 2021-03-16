#include "Light.h"

Light::Light(LightType lightType, Point3D position, Point3D direction, ColorUnion color)
{
	this->lightType = lightType;
	this->position = position;
	this->direction = direction;
	this->color = color;
}

LightType Light::GetLightType()
{
	return lightType;
}

Point3D Light::GetPosition()
{
	return position;
}

Point3D Light::GetDirection()
{
	return direction;
}

ColorUnion Light::GetColor()
{
	return color;
}