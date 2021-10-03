#pragma once

#include <windows.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <string>
#include <dwrite.h>

#define BUFFERS_COUNT 100

#define BRUSHES_COUNT 4
#define BRUSH_BLACK_TRANSPARENT 0
#define BRUSH_YELLOW_TRANSPARENT 1
#define BRUSH_RED_TRANSPARENT 2
#define BRUSH_WHITE 3

struct Buffer {
	ID2D1Bitmap* dxBuffer = nullptr;
	char filename[MAX_PATH] = "";
};



class BuffersList
{
public:

	BuffersList();

	int add(ID2D1Bitmap* pBuffer, const char* filename);
	ID2D1Bitmap* getBuffer(int id);
private:
	Buffer* buffers[BUFFERS_COUNT];
	int getBufferIdByFile(const char* filename);
};



class GraphicSystem
{
public:
	BOOL init(HWND hWnd);
	
	void draw( int bufferID, 
		float from_X, float from_Y, float from_W, float from_H, 
		float to_X, float to_Y, float to_W, float to_H
	);

	int createSurfaceFromFile(const char* filename);

	void beginDraw();
	void endDraw();

	void fillRectangle(int left, int top, int right, int bottom, int brush_id);
	void drawRectangle(int left, int top, int right, int bottom, int brush_id);

	void text(WCHAR* str, int x, int y, int w, int h);

	GraphicSystem();
	~GraphicSystem();

	




private:

	void createBrushes();

	ID2D1Factory* pD2DFactory = nullptr;
	ID2D1HwndRenderTarget* pRenderTarget = nullptr;
	BuffersList buffers;
	ID2D1SolidColorBrush* brushes[BRUSHES_COUNT] = {0};
	IDWriteFactory* m_pDWriteFactory = nullptr;
	IDWriteTextFormat* m_pTextFormat = nullptr;

	BOOL CreateBitmapFromFile(PCWSTR uri, ID2D1Bitmap** ppBitmap);


	
};

