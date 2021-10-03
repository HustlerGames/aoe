#pragma once

#include "../../Wnd.h"
#include "../Controls/Button1.h"
#include "../../../World/Objects/Buildings/BuildingCenter.h"

class BuildingTasksCenter : public Wnd
{
public:
	BuildingCenter* targetBuilding = nullptr;
	Button1* buttonTaskPeasant = nullptr;
	
	BuildingTasksCenter();
	GuiImage image;
	void render();

};