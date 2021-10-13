#include "PanelCurrentTasks.h"

PanelCurrentTasks::PanelCurrentTasks()
{
	// позиция в абсолютных координатах
	// 522x84

	position.left = 677;
	position.top = 994;
	position.right = position.left + 522;
	position.bottom = position.top + 84;
}

void PanelCurrentTasks::render()
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

	BuildingTask* task = targetBuilding->tasks.root;

	int border = 10;
	int icon_num = 1;

	int icon_left;
	int icon_top;
	int indicator_width;

	while (task)
	{
		SpriteResource* res = (SpriteResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_CATEGORY_GUI)
			->get(task->id);

		icon_left = position.left + border * icon_num;
		icon_top = position.top + border;

		indicator_width = task->counter / task->quantity;

		// иконка
		GS.draw(
			res->bufferID,
			res->frame.x,
			res->frame.y,
			res->frame.width,
			res->frame.height,
			icon_left,
			icon_top,
			res->frame.width,
			res->frame.height
		);

		// индикатор прогресса
		GS.fillRectangle(
			icon_left,
			icon_top,
			icon_left + indicator_width,
			icon_top + res->frame.height,
			BRUSH_YELLOW_TRANSPARENT
		);

		// подпись кол-ва
		//WCHAR str[4] = {0};
		//const size_t cSize = strlen(c) + 1;
		//wchar_t* wc = new wchar_t[cSize];
		//mbstowcs(wc, c, cSize);
		// 
		//WCHAR str[] = _itow(task->quantity, str);
		//GS.text( str, icon_left + 5, icon_top + 5, 1200, 200);

		icon_num++;
		task = task->next;
	}


}

void PanelCurrentTasks::onLMouse(int x, int y)
{
	BuildingTask* task = getTask(x, y);
	if (task) {
		targetBuilding->addTask(task->id, 1);
	}
}

void PanelCurrentTasks::onRMouse(int x, int y)
{
	BuildingTask* task = getTask(x, y);
	if (task) {
		targetBuilding->removeTask(task);
	}
}

BuildingTask* PanelCurrentTasks::getTask(int x, int y)
{
	int border = 10;
	int icon_left;
	int icon_top;
	int icon_num = 1;

	BuildingTask* task = targetBuilding->tasks.root;
	while (task)
	{
		SpriteResource* res = (SpriteResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_CATEGORY_GUI)
			->get(task->id);

		icon_left = position.left + border * icon_num;
		icon_top = position.top + border;

		if (x >= icon_left && x <= (icon_left + res->frame.width) &&
			y >= icon_top && y <= icon_top + res->frame.height)
			return task;

		icon_num++;
		task = task->next;
	}

	return nullptr;
}