#pragma once

#include "TaskBuilding.h"


class Barracks : public TaskBuilding
{
public:

	Barracks();
	void update();
	bool addTask(int task_id, int quantity);
	bool executeTask(int task_id);
	bool createArcher();
	bool createSwordsman();
};