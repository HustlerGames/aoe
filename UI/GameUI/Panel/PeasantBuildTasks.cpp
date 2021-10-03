#include "PeasantBuildTasks.h"
#include "../../../Handler/Handler.h"


extern Handler handler;


void onPeasantBuildHomeClick(Button1* button) {
	handler.setBuildMode(BUILDING_HOME);
}
void onPeasantBuildCenterClick(Button1* button) {
	handler.setBuildMode(BUILDING_CENTER);
}
void onPeasantBuildStoreClick(Button1* button) {
	handler.setBuildMode(BUILDING_STORE);
}
void onPeasantBuildBarracksClick(Button1* button) {
	handler.setBuildMode(BUILDING_BARRACKS);
}
void onPeasantBuildFenceClick(Button1* button) {
	handler.setBuildMode(BUILDING_FENCE);
}
void onPeasantBuildTowerClick(Button1* button) {
	handler.setBuildMode(BUILDING_TOWER1);
}


PeasantBuildTasks::PeasantBuildTasks()
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
		->get(RESOURCE_CATEGORY_GUI)->get(PEASANT_TASK_CREATE_HOME);

	buildHome = new Button1;
	buildHome->image.bufferID = spBtnRes->bufferID;
	buildHome->image.frame = spBtnRes->frame;
	buildHome->visible = true;
	buildHome->onButtonClick = onPeasantBuildHomeClick;
	buildHome->position = { position.left + 10, position.left + 10 + 60, position.top + 10, position.top + 10 + 60 };

	spBtnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(PEASANT_TASK_CREATE_CENTER);

	buildCenter = new Button1;
	buildCenter->image.bufferID = spBtnRes->bufferID;
	buildCenter->image.frame = spBtnRes->frame;
	buildCenter->visible = true;
	buildCenter->onButtonClick = onPeasantBuildCenterClick;
	buildCenter->position = { position.left + 10 + (60 + 5), position.left + 10 + (60 + 5) + 60, position.top + 10, position.top + 10 + 60 };

	spBtnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(PEASANT_TASK_CREATE_STORE);

	buildStore = new Button1;
	buildStore->image.bufferID = spBtnRes->bufferID;
	buildStore->image.frame = spBtnRes->frame;
	buildStore->visible = true;
	buildStore->onButtonClick = onPeasantBuildStoreClick;
	buildStore->position = { position.left + 10 + (60 + 5)*2, position.left + 10 + (60 + 5)*2 + 60, position.top + 10, position.top + 10 + 60 };

	spBtnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(PEASANT_TASK_CREATE_BARRACKS);

	buildBarracks = new Button1;
	buildBarracks->image.bufferID = spBtnRes->bufferID;
	buildBarracks->image.frame = spBtnRes->frame;
	buildBarracks->visible = true;
	buildBarracks->onButtonClick = onPeasantBuildBarracksClick;
	buildBarracks->position = { position.left + 10 + (60 + 5) * 3, position.left + 10 + (60 + 5) * 3 + 60, position.top + 10, position.top + 10 + 60 };

	spBtnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(PEASANT_TASK_CREATE_FENCE);

	buildFence = new Button1;
	buildFence->image.bufferID = spBtnRes->bufferID;
	buildFence->image.frame = spBtnRes->frame;
	buildFence->visible = true;
	buildFence->onButtonClick = onPeasantBuildFenceClick;
	buildFence->position = { position.left + 10 + (60 + 5) * 4, position.left + 10 + (60 + 5) * 4 + 60, position.top + 10, position.top + 10 + 60 };

	spBtnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(PEASANT_TASK_CREATE_TOWER);

	buildTower = new Button1;
	buildTower->image.bufferID = spBtnRes->bufferID;
	buildTower->image.frame = spBtnRes->frame;
	buildTower->visible = true;
	buildTower->onButtonClick = onPeasantBuildTowerClick;
	buildTower->position = { position.left + 10 + (60 + 5) * 5, position.left + 10 + (60 + 5) * 5 + 60, position.top + 10, position.top + 10 + 60 };

	add(buildHome);
	add(buildCenter);
	add(buildStore);
	add(buildBarracks);
	add(buildFence);
	add(buildTower);
}

void PeasantBuildTasks::render()
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