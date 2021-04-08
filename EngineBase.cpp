#include <vector>
#include <algorithm>
#include "framework.h"
#include "Settings.h"
#include "Point3D.h"
#include "EngineBase.h"
#include "GameObjectBase.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "Windowscodecs.lib")

double EngineBase::Z0 = (RESOLUTION_X / 2.0) / tan((FIELD_OF_VIEW / 2.0) * 3.14159265 / 180.0);

EngineBase::EngineBase() : m_pDirect2dFactory(NULL), m_pRenderTarget(NULL)
{
	srand(time(NULL));

	camera = new Camera();
}

EngineBase::~EngineBase()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
}

HRESULT EngineBase::InitializeD2D(HWND m_hwnd)
{
    // Initializes Direct2D, for drawing
    D2D1_SIZE_U size = D2D1::SizeU(RESOLUTION_X, RESOLUTION_Y);
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
    m_pDirect2dFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hwnd, size, V_SYNC ? D2D1_PRESENT_OPTIONS_NONE : D2D1_PRESENT_OPTIONS_IMMEDIATELY),
        &m_pRenderTarget
    );

	m_pRenderTarget->CreateBitmap(D2D1::SizeU(RESOLUTION_X, RESOLUTION_Y), D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)), &pBitmap);

    return S_OK;
}

void EngineBase::MousePosition(int x, int y)
{
    mousePosition.x = x;
    mousePosition.y = y;
}

void EngineBase::KeyUp(WPARAM wParam)
{
	camera->HandleKeyUp(wParam);
}

void EngineBase::KeyDown(WPARAM wParam)
{
	camera->HandleKeyDown(wParam);
}

void EngineBase::MouseButtonUp(bool left, bool right)
{
}

void EngineBase::MouseButtonDown(bool left, bool right)
{
}

void EngineBase::AddGameObject(GameObjectBase* gameObj)
{
	gameObj->engine = this;
	objectList.push_back(gameObj);
}

void EngineBase::RemoveGameObject(GameObjectBase* gameObj)
{
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] == gameObj)
		{
			objectList.erase(objectList.begin() + i);
			return;
		}
	}
}

void EngineBase::AddLight(Light* light)
{
	lights.push_back(light);
}

void EngineBase::RemoveLight(Light* light)
{
	for (int i = 0; i < lights.size(); i++)
	{
		if (lights[i] == light)
		{
			lights.erase(lights.begin() + i);
			return;
		}
	}
}

void EngineBase::Logic(double elapsedTime)
{
    for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->Logic(elapsedTime);
	}

	camera->Logic(elapsedTime);
}

HRESULT EngineBase::Draw()
{
    // Draws the elements in the game using Direct2D
    HRESULT hr;

    m_pRenderTarget->BeginDraw();

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	// Clear buffer vector
	memset(renderBuffer, 0, RESOLUTION_X * RESOLUTION_Y * 4);

	// Clear Z buffer
	memset(zBuffer, 0, RESOLUTION_X * RESOLUTION_Y * sizeof(double));

	// Get all triangles (translated into world based on object position)
	std::vector<Triangle*> allTriangles;
	for (int i = 0; i < objectList.size(); i++) {
		for (int j = 0; j < objectList[i]->triangles.size(); j++) {
			objectList[i]->triangles[j]->CalculateWorldPoints(objectList[i]->GetPosition(), objectList[i]->GetRotation());

			// Apply lights
			for (int k = 0; k < lights.size(); k++)
			{
				objectList[i]->triangles[j]->ApplyLight(lights[k]);
			}

			objectList[i]->triangles[j]->CalculateCameraView(camera);
			
			std::list<Triangle*> clippedTriangles = objectList[i]->triangles[j]->GetZClippedTriangles();
			for (Triangle* clippedTriangle : clippedTriangles)
			{
				allTriangles.push_back(clippedTriangle);
			}
		}
	}

	// Sort the triangles by average Z
	//std::sort(allTriangles.begin(), allTriangles.end(), Triangle::SortOrder);

	// Draw triangles in correct order
	for (int i = 0; i < allTriangles.size(); i++)
	{
		allTriangles[i]->CalculateDrawPoints();
		if (allTriangles[i]->GetNormalZ() < 0)
		{
			std::list<Triangle*> clippedTriangles = allTriangles[i]->GetClippedTriangles();
			for (Triangle* clippedTriangle : clippedTriangles)
			{
				clippedTriangle->Draw(renderBuffer, zBuffer);
				delete clippedTriangle;
			}
		}
		delete allTriangles[i];
	}

	if (ANTIALIASING) {
		AntiAliasing();
	}

	pBitmap->CopyFromMemory(nullptr, renderBuffer, RESOLUTION_X * 4);

	m_pRenderTarget->DrawBitmap(pBitmap, D2D1::RectF(0, 0, RESOLUTION_X, RESOLUTION_Y));

    hr = m_pRenderTarget->EndDraw();

    return S_OK;
}

ID2D1Bitmap* EngineBase::LoadImage(LPCWSTR imageFile)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICImagingFactory* pIWICFactory = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&pIWICFactory));

	HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
		imageFile,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	ID2D1Bitmap* toReturn = NULL;

	if (SUCCEEDED(hr))
	{

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			&toReturn
		);
	}

	SafeRelease(&pIWICFactory);
	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pConverter);

	return toReturn;
}

IWICBitmap* EngineBase::LoadImageInWIC(LPCWSTR imageFile)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICImagingFactory* pIWICFactory = NULL;
	UINT originalWidth = 0;
	UINT originalHeight = 0;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&pIWICFactory));

	HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
		imageFile,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		hr = pSource->GetSize(&originalWidth, &originalHeight);
	}

	IWICBitmap* toReturn = NULL;

	if (SUCCEEDED(hr))
	{

		hr = pIWICFactory->CreateBitmapFromSourceRect(
			pSource, 0, 0, (UINT)originalWidth, (UINT)originalHeight, &toReturn);
	}

	SafeRelease(&pIWICFactory);
	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pConverter);

	return toReturn;
}

double EngineBase::GetZ0()
{
	return EngineBase::Z0;
}

Point3D EngineBase::CalculateNormal(Point3D p1, Point3D p2, Point3D p3)
{
	// First normalize
	Point3D v1;
	v1.x = (p2.x - p1.x);
	v1.y = (p2.y - p1.y);
	v1.z = (p2.z - p1.z);
	double v1l = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	v1.x = v1.x / v1l;
	v1.y = v1.y / v1l;
	v1.z = v1.z / v1l;
	Point3D v2;
	v2.x = (p3.x - p1.x);
	v2.y = (p3.y - p1.y);
	v2.z = (p3.z - p1.z);
	double v2l = sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	v2.x = v2.x / v2l;
	v2.y = v2.y / v2l;
	v2.z = v2.z / v2l;
	// Calculate normal
	Point3D toReturn;
	toReturn.x = v1.y * v2.z - v1.z * v2.y;
	toReturn.y = v1.z * v2.x - v1.x * v2.z;
	toReturn.z = v1.x * v2.y - v1.y * v2.x;
	return toReturn;
}

double EngineBase::CalculateDotProduct(Point3D p1, Point3D p2)
{
	return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

Point3D EngineBase::Translate(Point3D original, Point3D translation)
{
	Point3D toReturn;
	toReturn.x = original.x + translation.x;
	toReturn.y = original.y + translation.y;
	toReturn.z = original.z + translation.z;
	toReturn.u = original.u;
	toReturn.v = original.v;
	toReturn.w = original.w;
	return toReturn;
}

Point3D EngineBase::Rotate(Point3D original, Point3D rotation)
{
	Point3D toReturn;
	// Rotation matrix: https://en.wikipedia.org/wiki/Rotation_matrix
	toReturn.x = original.x * (cos(rotation.z) * cos(rotation.y)) + 
				 original.y * (cos(rotation.z) * sin(rotation.y) * sin(rotation.x) - sin(rotation.z) * cos(rotation.x)) +
				 original.z * (cos(rotation.z) * sin(rotation.y) * cos(rotation.x) + sin(rotation.z) * sin(rotation.x));
	toReturn.y = original.x * (sin(rotation.z) * cos(rotation.y)) +
				 original.y * (sin(rotation.z) * sin(rotation.y) * sin(rotation.x) + cos(rotation.z) * cos(rotation.x)) +
				 original.z * (sin(rotation.z) * sin(rotation.y) * cos(rotation.x) - cos(rotation.z) * sin(rotation.x));
	toReturn.z = original.x * (- sin(rotation.y)) +
				 original.y * (cos(rotation.y) * sin(rotation.x)) +
				 original.z * (cos(rotation.y) * cos(rotation.x));
	toReturn.u = original.u;
	toReturn.v = original.v;
	toReturn.w = original.w;
	return toReturn;
}

Point3D EngineBase::ApplyPerspective(Point3D original)
{
	Point3D toReturn;
	toReturn.x = original.x * Z0 / (Z0 + original.z);
	toReturn.y = original.y * Z0 / (Z0 + original.z);
	toReturn.z = original.z;

	toReturn.u = original.u * Z0 / (Z0 + original.z);
	toReturn.v = original.v * Z0 / (Z0 + original.z);
	toReturn.w = original.w * Z0 / (Z0 + original.z);

	return toReturn;
}

Point3D EngineBase::CenterScreen(Point3D original)
{
	Point3D toReturn;
	toReturn.x = original.x + RESOLUTION_X / 2;
	toReturn.y = original.y + RESOLUTION_Y / 2;
	toReturn.z = original.z;
	toReturn.u = original.u;
	toReturn.v = original.v;
	toReturn.w = original.w;
	return toReturn;
}

void EngineBase::AntiAliasing() {

	for (int y = 1; y < RESOLUTION_Y - 1; y++) {
		for (int x = 1; x < RESOLUTION_X - 1; x++) {
			ColorUnion center = ColorUnion::Create(renderBuffer[y * RESOLUTION_X + x]);
			ColorUnion right = ColorUnion::Create(renderBuffer[y * RESOLUTION_X + x + 1]);
			ColorUnion down = ColorUnion::Create(renderBuffer[(y + 1) * RESOLUTION_X + x]);
			ColorUnion downright = ColorUnion::Create(renderBuffer[(y + 1) * RESOLUTION_X + x + 1]);
			center.colorItems.red = (unsigned char)(((int)center.colorItems.red + right.colorItems.red + down.colorItems.red + downright.colorItems.red) / 4.0);
			center.colorItems.green = (unsigned char)(((int)center.colorItems.green + right.colorItems.green + down.colorItems.green + downright.colorItems.green) / 4.0);
			center.colorItems.blue = (unsigned char)(((int)center.colorItems.blue + right.colorItems.blue + down.colorItems.blue + downright.colorItems.blue) / 4.0);
			center.colorItems.alpha = (unsigned char)(((int)center.colorItems.alpha + right.colorItems.alpha + down.colorItems.alpha + downright.colorItems.alpha) / 4.0);
			renderBuffer[y * RESOLUTION_X + x] = center.color;
		}
	}

}