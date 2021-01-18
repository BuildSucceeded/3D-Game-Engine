#include "Settings.h"
#include "Point3D.h"
#include "Triangle.h"
#include "EngineBase.h"

Triangle::Triangle(Point3D p0, Point3D p1, Point3D p2, Texture* t)
{
	points[0] = p0;
	points[1] = p1;
	points[2] = p2;
	texture = t;
}

void Triangle::CalculateWorldPoints(Point3D position, Point3D rotation)
{
	// Rotate
	for (int i = 0; i < 3; i++)
		worldPoints[i] = EngineBase::Rotate(points[i], rotation);

	// Translate
	for (int i = 0; i < 3; i++)
		worldPoints[i] = EngineBase::Translate(worldPoints[i], position);

	// Average Z (for sorting triangles)
	averageZ = (worldPoints[0].z + worldPoints[1].z + worldPoints[2].z) / 3.0;
}

void Triangle::CalculateDrawPoints()
{
	// Apply perspective
	for (int i = 0; i < 3; i++)
		drawPoints[i] = EngineBase::ApplyPerspective(worldPoints[i]);

	// Center screen
	for (int i = 0; i < 3; i++)
		drawPoints[i] = EngineBase::CenterScreen(drawPoints[i]);

	// Normal Z -  is the triangle facing us or the other way
	normalZ = (drawPoints[1].x - drawPoints[0].x) * (drawPoints[2].y - drawPoints[0].y) - (drawPoints[1].y - drawPoints[0].y) * (drawPoints[2].x - drawPoints[0].x);
}

void Triangle::Draw(int* renderBuffer)
{
	
	Point3D aux;
	if (drawPoints[0].y > drawPoints[1].y) {
		aux = drawPoints[0];
		drawPoints[0] = drawPoints[1];
		drawPoints[1] = aux;
	}
	if (drawPoints[0].y > drawPoints[2].y) {
		aux = drawPoints[0];
		drawPoints[0] = drawPoints[2];
		drawPoints[2] = aux;
	}
	if (drawPoints[1].y > drawPoints[2].y) {
		aux = drawPoints[1];
		drawPoints[1] = drawPoints[2];
		drawPoints[2] = aux;
	}

	int p0x = drawPoints[0].x;
	int p0y = drawPoints[0].y;
	int p1x = drawPoints[1].x;
	int p1y = drawPoints[1].y;
	int p2x = drawPoints[2].x;
	int p2y = drawPoints[2].y;

	int texWidth = texture->GetWidth();
	int texHeight = texture->GetHeight();

	if (p0y < p1y) {
		double slope1 = ((double)p1x - p0x) / (p1y - p0y);
		double slope2 = ((double)p2x - p0x) / (p2y - p0y);
		for (int i = 0; i <= p1y - p0y; i++) {
			int x1 = p0x + i * slope1;
			int x2 = p0x + i * slope2;
			int y = p0y + i;

			double us = drawPoints[0].u + ((double)y - p0y) / (p1y - p0y) * (drawPoints[1].u - drawPoints[0].u);
			double vs = drawPoints[0].v + ((double)y - p0y) / (p1y - p0y) * (drawPoints[1].v - drawPoints[0].v);
			double ws = drawPoints[0].w + ((double)y - p0y) / (p1y - p0y) * (drawPoints[1].w - drawPoints[0].w);

			double ue = drawPoints[0].u + ((double)y - p0y) / (p2y - p0y) * (drawPoints[2].u - drawPoints[0].u);
			double ve = drawPoints[0].v + ((double)y - p0y) / (p2y - p0y) * (drawPoints[2].v - drawPoints[0].v);
			double we = drawPoints[0].w + ((double)y - p0y) / (p2y - p0y) * (drawPoints[2].w - drawPoints[0].w);

			if (x1 > x2) {
				int aux = x1;
				x1 = x2;
				x2 = aux;
				double aux2 = us;
				us = ue;
				ue = aux2;
				aux2 = vs;
				vs = ve;
				ve = aux2;
				aux2 = ws;
				ws = we;
				we = aux2;
			}
			if (x2 > x1) {
				double u = us * texWidth;
				double ustep = (ue - us) / (x2 - x1) * texWidth;
				double v = vs * texHeight;
				double vstep = (ve - vs) / (x2 - x1) * texHeight;
				double w = ws;
				double wstep = (we - ws) / (x2 - x1);
				for (int j = 0; j <= x2 - x1; j++) {
					int x = x1 + j;
					u += ustep;
					v += vstep;
					w += wstep;
					renderBuffer[RESOLUTION_X * y + x] = texture->GetValue(u / w, v / w);
				}
			}
		}
	}
	if (p1y < p2y) {
		double slope1 = ((double)p2x - p1x) / (p2y - p1y);
		double slope2 = ((double)p2x - p0x) / (p2y - p0y);
		double sx = p2x - (p2y - p1y) * slope2;
		for (int i = 0; i <= p2y - p1y; i++) {
			int x1 = p1x + i * slope1;
			int x2 = sx + i * slope2;
			int y = p1y + i;

			double us = drawPoints[1].u + ((double)y - p1y) / (p2y - p1y) * (drawPoints[2].u - drawPoints[1].u);
			double vs = drawPoints[1].v + ((double)y - p1y) / (p2y - p1y) * (drawPoints[2].v - drawPoints[1].v);
			double ws = drawPoints[1].w + ((double)y - p1y) / (p2y - p1y) * (drawPoints[2].w - drawPoints[1].w);

			double ue = drawPoints[0].u + ((double)y - p0y) / (p2y - p0y) * (drawPoints[2].u - drawPoints[0].u);
			double ve = drawPoints[0].v + ((double)y - p0y) / (p2y - p0y) * (drawPoints[2].v - drawPoints[0].v);
			double we = drawPoints[0].w + ((double)y - p0y) / (p2y - p0y) * (drawPoints[2].w - drawPoints[0].w);

			if (x1 > x2) {
				int aux = x1;
				x1 = x2;
				x2 = aux;
				double aux2 = us;
				us = ue;
				ue = aux2;
				aux2 = vs;
				vs = ve;
				ve = aux2;
				aux2 = ws;
				ws = we;
				we = aux2;
			}
			if (x2 > x1) {
				double u = us * texWidth;
				double ustep = (ue - us) / (x2 - x1) * texWidth;
				double v = vs * texHeight;
				double vstep = (ve - vs) / (x2 - x1) * texHeight;
				double w = ws;
				double wstep = (we - ws) / (x2 - x1);
				for (int x = x1; x <= x2; x++) {
					u += ustep;
					v += vstep;
					w += wstep;
					renderBuffer[RESOLUTION_X * y + x] = texture->GetValue(u / w, v / w);
				}
			}
		}
	}

}

bool Triangle::SortOrder(Triangle* triangle1, Triangle* triangle2)
{
	return triangle1->averageZ > triangle2->averageZ;
}

double Triangle::GetNormalZ()
{
	return normalZ;
}