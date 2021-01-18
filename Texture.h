#pragma once
#include "resource.h"
#include "framework.h"

class Texture
{
public:
	Texture(IWICBitmap* texture);
	~Texture();

	UINT GetWidth();
	UINT GetHeight();
	int GetValue(int x, int y);

private:
	UINT textureWidth;
	UINT textureHeight;
	int* textureMem;
};

