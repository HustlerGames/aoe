#pragma once

#include "../../Wnd.h"
#include "../Controls/Button1.h"
#include "../../../World/Objects/Buildings/Barracks.h"

class BuildingTasksBarracks : public Wnd
{
public:
	Barracks* targetBuilding = nullptr;
	Button1* buttonTaskSwordsman = nullptr;
	Button1* buttonTaskArcher = nullptr;

	BuildingTasksBarracks();
	GuiImage image;
	void render();
};