#include "framework.h"
#include "Point3D.h"
#include "EngineBase.h"
#include "GameObjectBase.h"

Point3D GameObjectBase::GetPosition()
{
	return this->position;
}