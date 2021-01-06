#include "framework.h"
#include "Settings.h"
#include "Point3D.h"
#include "EngineBase.h"
#include "GameObjectBase.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "Windowscodecs.lib")

EngineBase::EngineBase() : m_pDirect2dFactory(NULL), m_pRenderTarget(NULL)
{
	srand(time(NULL));
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

    return S_OK;
}

void EngineBase::MousePosition(int x, int y)
{
    mousePosition.x = x;
    mousePosition.y = y;
}

void EngineBase::KeyUp(WPARAM wParam)
{
}

void EngineBase::KeyDown(WPARAM wParam)
{
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
    objectList[noObjects] = gameObj;
	noObjects++;
}

void EngineBase::RemoveGameObject(GameObjectBase* gameObj)
{
	for (int i = 0; i < noObjects; i++)
	{
		if (objectList[i] == gameObj)
		{
			noObjects--;
			for (int j = i; j < noObjects; j++)
			{
				objectList[j] = objectList[j + 1];
			}
			return;
		}
	}
}

void EngineBase::Logic(double elapsedTime)
{
    for (int i = 0; i < noObjects; i++)
	{
		objectList[i]->Logic(elapsedTime);
	}
}

HRESULT EngineBase::Draw()
{
    // Draws the elements in the game using Direct2D
    HRESULT hr;

    m_pRenderTarget->BeginDraw();

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());


    m_pRenderTarget->Clear(D2D1::ColorF(D2D_BACKGROUND_COLOR));

    

    for (int i = 0; i < noObjects; i++)
		objectList[i]->Draw(m_pRenderTarget);



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
