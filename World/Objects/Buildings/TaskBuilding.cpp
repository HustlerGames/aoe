#include "TaskBuilding.h"

void TaskBuilding::updateTasks()
{
	BuildingTask* task = tasks.root;

	while (task)
	{
		task->counter++;
		if (task->counter > task->duration)
		{
			executeTask(task);

			task->counter = 0;
			task->quantity--;
			if (task->quantity == 0)
			{
				tasks.remove(task);
			}
		}

		task = task->next;
	}
}

bool TaskBuilding::addTask(int task_id, int quantity)
{
	return false;
}

void TaskBuilding::executeTask(int task_id)
{

}

bool TaskBuilding::hasRunningTask(int task_id)
{
	BuildingTask* task = tasks.root;

	while (task)
	{
		if (task->id == task_id)
			return true;

		task = task->next;
	}

	return false;
}


bool TaskBuilding::removeTask(BuildingTask* task)
{
	tasks.remove(task);
}