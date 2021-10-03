#pragma once

#include "../../Wnd.h"
#include "../Controls/Button1.h"

class PeasantBuildTasks : public Wnd
{
public:
	Button1* buildHome = nullptr;
	Button1* buildCenter = nullptr;
	Button1* buildStore = nullptr;
	Button1* buildBarracks = nullptr;
	Button1* buildFence = nullptr;
	Button1* buildTower = nullptr;

	PeasantBuildTasks();
	GuiImage image;
	void render();

};