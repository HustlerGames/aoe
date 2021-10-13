#pragma once

#include "GraphicSystem/GraphicSystem.h"
#include "UI/Wnd.h"
#include <vector>
#include <memory>

class GUI
{
public:
	std::vector<std::shared_ptr<Wnd>> wndList;
	void render();
	bool onLMouse(int x, int y);
	bool onRMouse(int x, int y);
	bool isInsideWnd(int x, int y);
	void add(Wnd* child);
	void init();
};

