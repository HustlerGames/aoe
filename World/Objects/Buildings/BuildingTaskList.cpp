#include "BuildingTaskList.h"

/*
* Добавляет задачу в конец очереди задач
*/
inline void BuildingTaskList::add(BuildingTask* task)
{
	task->next = nullptr;

	if (end)
	{
		end->next = task;
		end = task;
	}
	else
	{
		end = task;
		root = task;
		task->prev = nullptr;
	}
}

/*
* Удаляет задачу из очереди
*/
inline void BuildingTaskList::remove(BuildingTask* task)
{
	if (task->prev)
		task->prev->next = task->next;

	if (task->next)
		task->next->prev = task->prev;

	if (root == task)
		root = task->next;

	if (end == task)
		end = task->prev;

	delete task;

}

BuildingTaskList::~BuildingTaskList()
{
	while (root)
	{
		BuildingTask* task = root;
		root = root->next;
		delete task;
	}
}