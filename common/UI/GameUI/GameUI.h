#pragma once

#include "UI/GUI.h"
#include "Panel/Panel.h"
#include "Menu/Menu.h"
#include "Header/Header.h"

class GameUI : public GUI
{
public:
	Panel* panel = nullptr;
	Header* header = nullptr;
	Menu* menu = nullptr;

	void init();
};

