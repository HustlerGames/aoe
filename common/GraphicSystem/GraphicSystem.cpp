#include "GraphicSystem.h"

#include "wincodec.h"
#include <math.h>
#include <string>
#include <direct.h>



BuffersList::BuffersList()
{
	for (int i = 0; i < BUFFERS_COUNT; i++)
	{
		buffers[i] = nullptr;
	}
}

int BuffersList::add(ID2D1Bitmap* pBuffer, const char* filename) {
	
	int bufferID = getBufferIdByFile(filename);

	if (bufferID >= 0)
		return bufferID;

	for (int i = 0; i < BUFFERS_COUNT; i++)
	{
		if (buffers[i] == nullptr) {
			buffers[i] = new Buffer;
			buffers[i]->dxBuffer = pBuffer;
			strcpy_s(buffers[i]->filename, MAX_PATH, filename);

			return i;
		}
	}

	return -1;
}

ID2D1Bitmap* BuffersList::getBuffer(int id)
{
	if (id >= 0 && id < BUFFERS_COUNT)
		return buffers[id]->dxBuffer;

	return nullptr;
}

int BuffersList::getBufferIdByFile(const char* filename)
{
	for (int i = 0; i < BUFFERS_COUNT; i++)
	{
		if (buffers[i])
		{
			if (strcmp(buffers[i]->filename, filename) == 0)  return i;
		}
	}

	return -1;
}



GraphicSystem::GraphicSystem()
{
	pD2DFactory = NULL;
	pRenderTarget = NULL;
}


BOOL GraphicSystem::init(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	if (FAILED(hr)) return FALSE;

	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
		),
		&pRenderTarget
	);

	if (FAILED(hr)) return FALSE;

	// brushes
	createBrushes();

	// init font

	const WCHAR msc_fontName[] = L"Verdana";
	const FLOAT msc_fontSize = 14;

	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
	);

	m_pDWriteFactory->CreateTextFormat(
		msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		msc_fontSize,
		L"", //locale
		&m_pTextFormat
	);

	return TRUE;
}



void GraphicSystem::createBrushes()
{
	HRESULT hr;

	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f)),
		&brushes[BRUSH_WHITE]
	);

	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.97f)),
		&brushes[BRUSH_BLACK_TRANSPARENT]
	);

	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(1.0f, 1.0f, 0.0f, 0.7f)),
		&brushes[BRUSH_YELLOW_TRANSPARENT]
	);

	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(1.0f, 0.0f, 0.0f, 0.7f)),
		&brushes[BRUSH_RED_TRANSPARENT]
	);

	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0f)),
		&brushes[BRUSH_RED]
	);

	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f)),
		&brushes[BRUSH_GREEN]
	);

	/*
	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0.93f, 0.94f, 0.96f, 1.0f)),
		&brushes[ID]
	);
	*/

}

BOOL GraphicSystem::CreateBitmapFromFile(PCWSTR uri, ID2D1Bitmap** ppBitmap) {

	IWICImagingFactory* d2dWICFactory = NULL;
	IWICBitmapDecoder* d2dDecoder = NULL;
	IWICFormatConverter* d2dConverter = NULL;
	IWICBitmapFrameDecode* d2dBmpSrc = NULL;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (FAILED(hr)) return FALSE;

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWICImagingFactory),
		(void**)(&d2dWICFactory)
	);

	if (FAILED(hr)) return FALSE;

	hr = d2dWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&d2dDecoder
	);

	if (FAILED(hr)) return FALSE;

	hr = d2dWICFactory->CreateFormatConverter(&d2dConverter);

	if (FAILED(hr)) return FALSE;

	hr = d2dDecoder->GetFrame(0, &d2dBmpSrc);

	if (FAILED(hr)) return FALSE;

	hr = d2dConverter->Initialize(
		d2dBmpSrc,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
	);

	if (FAILED(hr)) return FALSE;

	hr = pRenderTarget->CreateBitmapFromWicBitmap(
		d2dConverter,
		NULL,
		ppBitmap
	);

	if (FAILED(hr)) return FALSE;


	if (d2dWICFactory) d2dWICFactory->Release();
	if (d2dDecoder) d2dDecoder->Release();
	if (d2dConverter) d2dConverter->Release();
	if (d2dBmpSrc) d2dBmpSrc->Release();

	CoUninitialize();

	return TRUE;
}

void GraphicSystem::text(WCHAR* str, int x, int y, int w, int h)
{
	pRenderTarget->DrawText(
		str,
		wcslen(str),
		m_pTextFormat,
		D2D1::RectF(x, y, w, h),
		brushes[BRUSH_WHITE]
	);
}

void GraphicSystem::beginDraw()
{

	if (pRenderTarget) {
		pRenderTarget->BeginDraw();
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}
}

void GraphicSystem::endDraw()
{
	pRenderTarget->EndDraw();
}


void GraphicSystem::draw(int bufferID, float from_X, float from_Y, float from_W, float from_H, float to_X, float to_Y, float to_W, float to_H)
{
	pRenderTarget->DrawBitmap(
		buffers.getBuffer(bufferID),
		D2D1::RectF(to_X, to_Y, to_X + to_W, to_Y + to_H),
		1,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,     //D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(from_X, from_Y, from_X + from_W, from_Y + from_H)
	);
}


int GraphicSystem::createSurfaceFromFile(const char* filename)
{
	std::string cfilename(filename);
	std::wstring wfilename(cfilename.begin(), cfilename.end());

	ID2D1Bitmap* pBitmap;
	CreateBitmapFromFile(wfilename.c_str(), &pBitmap);
	return buffers.add(pBitmap, filename);
}

void GraphicSystem::fillRectangle(int left, int top, int right, int bottom, int brush_id)
{
	pRenderTarget->FillRectangle(
		D2D1::RectF(
			left,
			top,
			right,
			bottom
		),
		brushes[brush_id]);
}

void GraphicSystem::drawRectangle(int left, int top, int right, int bottom, int brush_id)
{
	pRenderTarget->FillRectangle(
		D2D1::RectF(
			left,
			top,
			right,
			bottom
		),
		brushes[brush_id]);
}

GraphicSystem::~GraphicSystem()
{
	if (m_pDWriteFactory)
	{
		m_pDWriteFactory->Release();
		m_pDWriteFactory = nullptr;
	}

	if (pRenderTarget) {
		pRenderTarget->Release();
		pRenderTarget = NULL;
	}

	if (pD2DFactory) {
		pD2DFactory->Release();
		pD2DFactory = NULL;
	}
}









