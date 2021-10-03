#pragma once

#include <vector>
#include "../GraphicSystem/GraphicSystem.h"
#include <memory>
#include "../Resources/Resources.h"

extern GraphicSystem GS;
extern Resources resources;

struct GuiImage {
	int bufferID;
	Frame frame;
};


struct Position 
{
	int left;
	int right;
	int top;
	int bottom;
};

class Wnd
{
public:
	Position position;
	int color = BRUSH_BLACK_TRANSPARENT;
	Wnd* parent = nullptr;
	std::vector<std::shared_ptr<Wnd>> wndList;
	bool visible = true;
	
	Wnd();
	~Wnd();


	bool isInner(int x, int y);
	virtual void render();
	virtual void onLMouse(int x, int y);
	virtual void onRMouse(int x, int y);

	void add(Wnd* child);
};