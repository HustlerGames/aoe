#include "Peasant.h"
#include "Tasks/Tasks.h"
#include "Actions/Actions.h"


Peasant::Peasant()
{
	unit_type = UNIT_PEASANT;
	speed = 3;

	bag.count = 0;
	bag.max_count = 10;
	bag.resourceType = 0;

	addTask(new TaskAttack(this));
	addTask(new TaskHarvest(this));
	addTask(new TaskBuild(this));
	addAction(new ActionHit(this));
	addAction(new ActionHarvestIron(this));
	addAction(new ActionHarvestFood(this));
	addAction(new ActionHarvestWood(this));
	addAction(new ActionBuild(this));
}

void Peasant::putBag(BuildingStore* pStore)
{
	pStore->put(bag.count, bag.resourceType);
	bag.count = 0;
}
