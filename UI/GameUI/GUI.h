#pragma once

#include "../../GraphicSystem/GraphicSystem.h"
#include "../Wnd.h"
#include <vector>
#include <memory>
#include "Panel/Panel.h"
#include "Header/Header.h"
#include "Menu/Menu.h"

class GUI
{
public:
	Panel* panel = nullptr;
	Header* header = nullptr;
	Menu* menu = nullptr;


	std::vector<std::shared_ptr<Wnd>> wndList;
	void render();
	bool onLMouse(int x, int y);
	bool onRMouse(int x, int y);
	bool isInsideWnd(int x, int y);
	void add(Wnd* child);
	void init();
};

