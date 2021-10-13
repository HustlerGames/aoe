#pragma once

#include "Building.h"
#include "BuildingTaskList.h"

class TaskBuilding : public Building
{
public:

	BuildingTaskList tasks;

	void updateTasks();
	bool hasRunningTask(int task_id);

	virtual bool addTask(int task_id, int quantity);
	bool removeTask(BuildingTask* task);
	virtual void executeTask(BuildingTask* pTask);
	
};