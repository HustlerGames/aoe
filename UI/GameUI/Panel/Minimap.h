#pragma once

#include "../../Wnd.h"

class Minimap : public Wnd
{
public:
	GuiImage image;

	Minimap();

	void render();
};