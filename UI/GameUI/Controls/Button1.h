#pragma once

#include "../../Wnd.h"

class Button1 : public Wnd
{
public:

	Button1();
	GuiImage image;
	void (*onButtonClick)(Button1*);
	void onLMouse(int x, int y);
	void render();
};