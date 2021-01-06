#pragma once

struct Point3D
{
	double x;
	double y;
	double z;

	static Point3D Create(double x, double y, double z)
	{
		Point3D toReturn;
		toReturn.x = x;
		toReturn.y = y;
		toReturn.z = z;
		return toReturn;
	}
};