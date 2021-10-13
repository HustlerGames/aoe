#include "BuildingTasksCenter.h"
#include "../../../World/Objects/Buildings/BuildingTaskIDs.h"

void onCommandPeasantClick(Button1* button)
{
	((BuildingTasksCenter*)button->parent)
		->targetBuilding->addTask(BUILDING_TASK_CREATE_PEASAND, 1);
}

BuildingTasksCenter::BuildingTasksCenter()
{
	// 512x144
	position.left = 682;
	position.right = position.left + 512;
	position.top = 850;
	position.bottom = position.top + 144;

	SpriteResource* spRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_COMMANDS);

	image.frame = spRes->frame;
	image.bufferID = spRes->bufferID;

	SpriteResource* spBtnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(BUILDING_TASK_CREATE_PEASANT);

	buttonTaskPeasant = new Button1;
	buttonTaskPeasant->image.bufferID = spBtnRes->bufferID;
	buttonTaskPeasant->image.frame = spBtnRes->frame;
	buttonTaskPeasant->visible = false;
	buttonTaskPeasant->onButtonClick = onCommandPeasantClick;
	buttonTaskPeasant->position = { position.left + 10, position.left + 10 + 60, position.top + 10, position.top + 10 + 60 };


	add(buttonTaskPeasant);

}

void BuildingTasksCenter::render()
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