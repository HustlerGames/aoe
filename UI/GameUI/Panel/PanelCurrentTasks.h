#pragma once

#include "../../Wnd.h"
#include "../../../World/Objects/Buildings/TaskBuilding.h"

class PanelCurrentTasks : public Wnd
{
public:
	
	TaskBuilding* targetBuilding = nullptr;

	PanelCurrentTasks();
	
	GuiImage image;

	void render();

	void onLMouse(int x, int y);
	void onRMouse(int x, int y);

	BuildingTask* getTask(int x, int y);

};