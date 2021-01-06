#include "Settings.h"
#include "Point3D.h"
#include "Cube.h"
#include "Engine.h"

Cube::Cube()
{
	position = Point3D::Create(0, 0, 400);
	rotation = Point3D::Create(0, 0, 0);

	points[0] = Point3D::Create(-200, -200, -200);
	points[1] = Point3D::Create(-200, 200, -200);
	points[2] = Point3D::Create(200, 200, -200);
	points[3] = Point3D::Create(200, -200, -200);
	points[4] = Point3D::Create(-200, -200, 200);
	points[5] = Point3D::Create(-200, 200, 200);
	points[6] = Point3D::Create(200, 200, 200);
	points[7] = Point3D::Create(200, -200, 200);
}

void Cube::Logic(double elapsedTime)
{
	rotation.y += 1 * elapsedTime;
}

void Cube::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	if (m_pWhiteBrush == NULL)
	{
		m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&m_pWhiteBrush
		);
	}

	Point3D drawPoints[8];
	
	// Rotate
	for (int i = 0; i < 8; i++)
		drawPoints[i] = engine->Rotate(points[i], rotation);

	// Translate
	for (int i = 0; i < 8; i++)
		drawPoints[i] = engine->Translate(drawPoints[i], position);

	// Apply perspective
	for (int i = 0; i < 8; i++)
		drawPoints[i] = engine->ApplyPerspective(drawPoints[i]);

	// Center screen
	for (int i = 0; i < 8; i++)
		drawPoints[i] = engine->CenterScreen(drawPoints[i]);

	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[0].x, drawPoints[0].y), D2D1::Point2F(drawPoints[1].x, drawPoints[1].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[1].x, drawPoints[1].y), D2D1::Point2F(drawPoints[2].x, drawPoints[2].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[2].x, drawPoints[2].y), D2D1::Point2F(drawPoints[3].x, drawPoints[3].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[3].x, drawPoints[3].y), D2D1::Point2F(drawPoints[0].x, drawPoints[0].y), m_pWhiteBrush, 4);

	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[4].x, drawPoints[4].y), D2D1::Point2F(drawPoints[5].x, drawPoints[5].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[5].x, drawPoints[5].y), D2D1::Point2F(drawPoints[6].x, drawPoints[6].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[6].x, drawPoints[6].y), D2D1::Point2F(drawPoints[7].x, drawPoints[7].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[7].x, drawPoints[7].y), D2D1::Point2F(drawPoints[4].x, drawPoints[4].y), m_pWhiteBrush, 4);

	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[0].x, drawPoints[0].y), D2D1::Point2F(drawPoints[4].x, drawPoints[4].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[1].x, drawPoints[1].y), D2D1::Point2F(drawPoints[5].x, drawPoints[5].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[2].x, drawPoints[2].y), D2D1::Point2F(drawPoints[6].x, drawPoints[6].y), m_pWhiteBrush, 4);
	m_pRenderTarget->DrawLine(D2D1::Point2F(drawPoints[3].x, drawPoints[3].y), D2D1::Point2F(drawPoints[7].x, drawPoints[7].y), m_pWhiteBrush, 4);

}