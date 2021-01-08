#include "Settings.h"
#include "Point3D.h"
#include "Triangle.h"
#include "EngineBase.h"

Triangle::Triangle(Point3D p0, Point3D p1, Point3D p2, D2D1::ColorF::Enum c)
{
	points[0] = p0;
	points[1] = p1;
	points[2] = p2;
	color = c;
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
}

void Triangle::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	if (m_pColorBrush == NULL)
	{
		m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(color),
			&m_pColorBrush
		);
	}

	ID2D1PathGeometry* clPath;
	ID2D1Factory* factory;
	m_pRenderTarget->GetFactory(&factory);
	factory->CreatePathGeometry(&clPath);

	ID2D1GeometrySink* pclSink;
	clPath->Open(&pclSink);
	pclSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	pclSink->BeginFigure(D2D1::Point2F(drawPoints[0].x, drawPoints[0].y), D2D1_FIGURE_BEGIN_FILLED);
	pclSink->AddLine(D2D1::Point2F(drawPoints[1].x, drawPoints[1].y));
	pclSink->AddLine(D2D1::Point2F(drawPoints[2].x, drawPoints[2].y));
	pclSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pclSink->Close();
	m_pRenderTarget->FillGeometry(clPath, m_pColorBrush);

	SafeRelease(&pclSink);
	SafeRelease(&clPath);
}

bool Triangle::SortOrder(Triangle* triangle1, Triangle* triangle2)
{
	return triangle1->averageZ > triangle2->averageZ;
}