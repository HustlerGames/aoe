#pragma once

#include "UI/Wnd.h"
#include "UI/GameUI/Controls/Button1.h"

class Menu : public Wnd
{
public:
	GuiImage image;

	Menu();

	void render();
};