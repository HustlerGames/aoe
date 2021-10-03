#pragma once

#include "Task.h"
#include "../../Units/Peasant.h"
#include "Structures.h"
#include "../../Resources/ObjectResource.h"
#include "../../Buildings/BuildingStore.h"

class Task;

class TaskHarvest : public Task
{
public:
	ObjectResource* resourceObject = nullptr;
	Peasant* peasant = nullptr;
	BuildingStore* pClosestStore = nullptr;

	bool needUnload();
	void harvestWood(ObjectResource* resObj);
	void harvestFood(ObjectResource* resObj);
	void harvestIron(ObjectResource* resObj);
	TaskHarvest(Unit* unit);
	BuildingStore* findClosestStore();
	ObjectResource* findClosestResource(int type);
	int execute();
	void set(StructTask* s);
};