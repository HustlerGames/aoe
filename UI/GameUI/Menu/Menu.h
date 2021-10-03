#pragma once

#include "../../Wnd.h"
#include "../Controls/Button1.h"

class Menu : public Wnd
{
public:
	GuiImage image;

	Menu();

	void render();
};