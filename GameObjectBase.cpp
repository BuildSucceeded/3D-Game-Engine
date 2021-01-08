#include "framework.h"
#include "Point3D.h"
#include "EngineBase.h"
#include "GameObjectBase.h"

Point3D GameObjectBase::GetPosition()
{
	return this->position;
}

void GameObjectBase::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	for (int i = 0; i < noTriangles; i++) {
		triangles[i]->Draw(m_pRenderTarget, position, rotation);
	}
}