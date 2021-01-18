#pragma once

struct Point3D
{
	double x;
	double y;
	double z;

	double u;
	double v;
	double w = 1;

	static Point3D Create(double x, double y, double z)
	{
		Point3D toReturn;
		toReturn.x = x;
		toReturn.y = y;
		toReturn.z = z;
		return toReturn;
	}

	static Point3D Create(double x, double y, double z, double u, double v)
	{
		Point3D toReturn;
		toReturn.x = x;
		toReturn.y = y;
		toReturn.z = z;
		toReturn.u = u;
		toReturn.v = v;
		return toReturn;
	}
};