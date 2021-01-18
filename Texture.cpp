#include "Texture.h"

Texture::Texture(IWICBitmap* texture)
{
	texture->GetSize(&textureWidth, &textureHeight);
	WICRect rcLock = { 0, 0, textureWidth, textureHeight };
	IWICBitmapLock* textureLock;
	texture->Lock(&rcLock, WICBitmapLockRead, &textureLock);

	textureMem = (int*)malloc(textureHeight * textureWidth * 4);
	texture->CopyPixels(&rcLock, textureWidth * 4, textureHeight * textureWidth * 4, (byte*)textureMem);
}

Texture::~Texture()
{
	delete textureMem;
}

UINT Texture::GetWidth()
{
	return textureWidth;
}

UINT Texture::GetHeight()
{
	return textureHeight;
}

int Texture::GetValue(int x, int y)
{
	if (x >= textureWidth)
		x = textureWidth - 1;
	if (y >= textureHeight)
		y = textureHeight - 1;
	return textureMem[y * textureWidth + x];
}
