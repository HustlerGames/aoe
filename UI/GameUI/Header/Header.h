#pragma once

#include "../../Wnd.h"

class Header : public Wnd
{
public:
	GuiImage image;

	Header();

	void render();
};