
#include "BuildingTasksBarracks.h"
#include "PanelCurrentTasks.h"
#include "World/Objects/Buildings/BuildingTaskIDs.h"

void onCommandArcherClick(Button1* button)
{
	((BuildingTasksBarracks*)button->parent)->targetBuilding->addTask(BUILDING_TASK_CREATE_ARCHER, 1);
}

void onCommandSwordsmanClick(Button1* button)
{
	((BuildingTasksBarracks*)button->parent)->targetBuilding->addTask(BUILDING_TASK_CREATE_SWORDSMAN, 1);
}


BuildingTasksBarracks::BuildingTasksBarracks()
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
		->get(RESOURCE_CATEGORY_GUI)->get(BUILDING_TASK_CREATE_SWORDSMAN);

	buttonTaskSwordsman = new Button1;
	buttonTaskSwordsman->image.bufferID = spBtnRes->bufferID;
	buttonTaskSwordsman->image.frame = spBtnRes->frame;
	buttonTaskSwordsman->visible = false;
	buttonTaskSwordsman->onButtonClick = onCommandSwordsmanClick;
	buttonTaskSwordsman->position = { position.left + 10, position.left + 10 + 60, position.top + 10, position.top + 10 + 60};


	spBtnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(BUILDING_TASK_CREATE_ARCHER);

	buttonTaskArcher = new Button1;
	buttonTaskArcher->image.bufferID = spBtnRes->bufferID;
	buttonTaskArcher->image.frame = spBtnRes->frame;
	buttonTaskArcher->visible = false;
	buttonTaskArcher->onButtonClick = onCommandArcherClick;
	buttonTaskSwordsman->position = { position.left + 10 + 60 + 10, position.left + 10 + 60 + 10 + 60, position.top + 10, position.top + 10 + 60 };

	add(buttonTaskSwordsman);
	add(buttonTaskArcher);


}

void BuildingTasksBarracks::render()
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