#pragma once

#include "../Wnd.h"

class ToggleButton : public Wnd
{
public:
	bool active = 0;
	int value = 0;
	GuiImage image;
	
	void (*onButtonActive)(ToggleButton*);

	void onLMouse(int x, int y);

	void render();
};