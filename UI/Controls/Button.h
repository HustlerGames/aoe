#pragma once

#include "../Wnd.h"

class Button : public Wnd
{
public:
	bool active = 0;
	int value = 0;
	GuiImage image;

	void (*onButtonClick)(Button*);

	void onLMouse(int x, int y);

	void render();
};