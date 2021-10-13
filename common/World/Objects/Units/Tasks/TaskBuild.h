#pragma once

#include "Task.h"
#include "../../Buildings/Building.h" 

class Task;

class TaskBuild : public Task
{
public:
	Building* pBuilding = nullptr;
	TaskBuild(Unit* unit);
	int execute();
	void set(StructTask* s);
	void build(Building* building);
};