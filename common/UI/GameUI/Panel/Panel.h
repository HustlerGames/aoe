#pragma once

#include "UI/Wnd.h"
#include "Minimap.h"
#include "ObjectInfo.h"
#include "BuildingTasksBarracks.h"
#include "BuildingTasksCenter.h"
#include "PeasantBuildTasks.h"
#include "PanelCurrentTasks.h"

class Panel : public Wnd
{
public:
	GuiImage image;
	Minimap* minimap = nullptr;
	BuildingTasksBarracks* pBuildingTasksBarracks = nullptr;
	BuildingTasksCenter* pBuildingTasksCenter = nullptr;
	PeasantBuildTasks* pPeasantBuildTasks = nullptr;
	ObjectInfo* pObjectInfo = nullptr;
	PanelCurrentTasks* pCurrentTasks = nullptr;
	
	Object* targetObject = nullptr;


	Panel();

	void hideAll();
	void render();

	void SetObject(Object* object);
};