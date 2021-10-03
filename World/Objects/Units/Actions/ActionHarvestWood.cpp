#include "ActionHarvestWood.h"
#include "../../Resources/ObjectResource.h"
#include "../Peasant.h"
#include "../../../../Sound/AudioSystem.h"

extern AudioSystem audio;

ActionHarvestWood::ActionHarvestWood(Unit* unit) : Action(unit)
{
	type = ACTION_HARVEST_WOOD;
	resourceObject = nullptr;
}

void ActionHarvestWood::execute()
{
	pUnit->updateDirection(resourceObject->position.x - pUnit->position.x, resourceObject->position.y - pUnit->position.y);
	counter++;
	if (counter > max_counter) {
		harvest();
		audio.play(SOUND_HARVEST_TREE);
		completed = true;
	}
}

void ActionHarvestWood::set(StructAction* st)
{
	StructActionHarvestWood* str = (StructActionHarvestWood*)st;
	resourceObject = (ObjectResource*)str->pTarget;
	counter = 0;
	completed = false;
}


void ActionHarvestWood::harvest()
{
	Peasant* peasant = (Peasant*)pUnit;

	if (peasant->bag.resourceType != resourceObject->resource_type)
	{
		peasant->bag.count = 0;
		peasant->bag.resourceType = resourceObject->resource_type;
	}

	int freeSpace = peasant->bag.max_count - peasant->bag.count;

	int queryCount = 1;
	if (freeSpace < queryCount) queryCount = freeSpace;
	peasant->bag.count += resourceObject->get(queryCount);
	completed = true;
}