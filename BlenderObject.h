#pragma once
#include "resource.h"
#include "framework.h"
#include "EngineBase.h"
#include "GameObjectBase.h"
#include "Point3D.h"

class BlenderObject : public GameObjectBase
{
public:
	BlenderObject(LPCWSTR objectFile, LPCWSTR textureFile, double scale);

	void Load();

	void Logic(double elapsedTime) override;

private:
	LPCWSTR objectFile;
	LPCWSTR textureFile;

	Texture* texture;

	double scale;

};

