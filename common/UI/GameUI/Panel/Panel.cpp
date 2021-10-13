#include "Panel.h"
#include "World/Objects/Units/Unit.h"
#include "World/Objects/Buildings/BuildingCenter.h"
#include "World/Objects/Buildings/Barracks.h"

Panel::Panel()
{
	position.left = 0;
	position.top = 815;
	position.right = 1920;
	position.bottom = 1080;

	SpriteResource* spRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_PANEL);

	image.frame = spRes->frame;
	image.bufferID = spRes->bufferID;

	minimap = new Minimap;
	add(minimap);

	pBuildingTasksBarracks = new BuildingTasksBarracks;
	pBuildingTasksBarracks->visible = false;
	add(pBuildingTasksBarracks);

	pBuildingTasksCenter = new BuildingTasksCenter;
	pBuildingTasksCenter->visible = false;
	add(pBuildingTasksCenter);

	pPeasantBuildTasks = new PeasantBuildTasks;
	pPeasantBuildTasks->visible = false;
	add(pPeasantBuildTasks);

	pObjectInfo = new ObjectInfo;
	add(pObjectInfo);

	pCurrentTasks = new PanelCurrentTasks;
	pCurrentTasks->visible = false;
	add(pCurrentTasks);
}

void Panel::hideAll()
{
	pBuildingTasksBarracks->visible = false;
	pBuildingTasksCenter->visible = false;
	pPeasantBuildTasks->visible = false;
	pCurrentTasks->visible = false;

}

void Panel::SetObject(Object* object)
{
	hideAll();

	if (object)
	{
		pObjectInfo->setObject(object);

		int objectType = object->getType();

		if (objectType == OBJECT_TYPE_UNIT)
		{
			Unit* unit = (Unit*)object;

			if (unit->unit_type == UNIT_PEASANT)
			{
				pPeasantBuildTasks->visible = true;
			}

			if (unit->unit_type == UNIT_ARCHER || unit->unit_type == UNIT_SWORDSMAN)
			{
				// TODO: STATE PANEL ACTIVATION
			}
		}

		if (objectType == OBJECT_TYPE_BUILDING)
		{
			Building* building = (Building*)object;
			if (building->building_type == BUILDING_CENTER)
			{
				TaskBuilding* taskBuilding = (TaskBuilding*)building;
				pCurrentTasks->targetBuilding = taskBuilding;
				pBuildingTasksCenter->targetBuilding = (BuildingCenter*)building;
				pBuildingTasksCenter->visible = true;
				pCurrentTasks->visible = true;
			}

			if (building->building_type == BUILDING_BARRACKS)
			{

				

				TaskBuilding* taskBuilding = (TaskBuilding*)building;
				pCurrentTasks->targetBuilding = taskBuilding;
				pCurrentTasks->visible = true;

				pBuildingTasksBarracks->targetBuilding = (Barracks*)building;
				pBuildingTasksBarracks->visible = true;
				
			}
		}
	} 
	

}

void Panel::render()
{
	// background
	GS.draw(
		image.bufferID,
		image.frame.x,
		image.frame.y,
		image.frame.width,
		image.frame.height,
		position.left,
		position.top,
		image.frame.width,  
		image.frame.height
	);

	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->visible)
			wndList[i]->render();
	}
}

