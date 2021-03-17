#include "Light.h"

Light::Light(LightType lightType, Point3D position, Point3D direction, ColorUnion color)
{
	this->lightType = lightType;
	this->position = position;
	this->direction = direction;
	this->color = color;
	this->length = 0;
}

Light::Light(LightType lightType, Point3D position, Point3D direction, ColorUnion color, double length)
{
	this->lightType = lightType;
	this->position = position;
	this->direction = direction;
	this->color = color;
	this->length = length;
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

double Light::GetLength()
{
	return length;
}