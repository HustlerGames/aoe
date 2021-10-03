#include "TaskHarvest.h"
#include "../../../Constants.h"
#include "../../../World.h"

extern World world;

TaskHarvest::TaskHarvest(Unit* unit) : Task(unit)
{
	type = TASK_TYPE_HARVEST;
	peasant = (Peasant*)unit;
}



int TaskHarvest::execute()
{
	BEGIN:
	if (!needUnload())
	{
		if (resourceObject->available == 0)
		{
			// find another resource
			ObjectResource* objRes = findClosestResource(resourceObject->resource_type);
			if (objRes) {
				resourceObject = objRes;
				goto BEGIN;
			} else 
				return TASK_STATE_CANCELLED;
		}


		if (peasant->distanceTo(resourceObject) < 2)
		{
			if(resourceObject->resource_type == OBJECT_RESOURCE_TYPE_FOOD)
				harvestFood(resourceObject);
			else if (resourceObject->resource_type == OBJECT_RESOURCE_TYPE_WOOD)
				harvestWood(resourceObject);
			else if (resourceObject->resource_type == OBJECT_RESOURCE_TYPE_IRON)
				harvestIron(resourceObject);
			return TASK_STATE_OK;
		}
		else
		{
			return peasant->moveToObject(resourceObject);
		}
	} 
	else
	{
		if (pClosestStore == nullptr)
		{
			pClosestStore = findClosestStore();
			if(pClosestStore == nullptr)
				return TASK_STATE_CANCELLED;
		}

		if (peasant->distanceTo(pClosestStore) < 2)
		{
			peasant->putBag(pClosestStore);
			goto BEGIN;
		}
		else
		{
			return peasant->moveToObject(pClosestStore);
		}
	}

	
}

void TaskHarvest::set(StructTask* s)
{
	StructTaskHarvest* p = (StructTaskHarvest*)s;
	resourceObject = (ObjectResource* )p->resourceObject;
	pClosestStore = nullptr;
}


bool TaskHarvest::needUnload()
{
	
	if (peasant->bag.count == peasant->bag.max_count)
		return true;

	return false;
}


void TaskHarvest::harvestFood(ObjectResource* resObj)
{
	StructActionHarvestFood st;
	st.type = ACTION_HARVEST_FOOD;
	st.pTarget = resObj;
	peasant->setAction(&st);
}



void TaskHarvest::harvestIron(ObjectResource* resObj)
{
	StructActionHarvestIron st;
	st.type = ACTION_HARVEST_IRON;
	st.pTarget = resObj;
	peasant->setAction(&st);
}




void TaskHarvest::harvestWood(ObjectResource* resObj)
{
	StructActionHarvestWood st;
	st.type = ACTION_HARVEST_WOOD;
	st.pTarget = resObj;
	peasant->setAction(&st);
}


BuildingStore* TaskHarvest::findClosestStore()
{

	Object* pObject;
	BuildingStore* pStore = nullptr;
	world.objects.save();
	world.objects.reset();
	while (pObject = world.objects.next())
	{
		if (pObject->getType() == OBJECT_TYPE_BUILDING)
		{
			Building* pBuilding = (Building*)pObject;
			if (pBuilding->building_type == BUILDING_STORE)
			{
				pStore = (BuildingStore*)pBuilding;
				break;
			}
		}
	}
	world.objects.restore();
	return pStore;
}


ObjectResource* TaskHarvest::findClosestResource(int type)
{

	Object* pObject;
	ObjectResource* pResFound = nullptr;
	world.objects.save();
	world.objects.reset();
	while (pObject = world.objects.next())
	{
		if (pObject->getType() == OBJECT_TYPE_RESOURCE)
		{
			ObjectResource* pRes = (ObjectResource*)pObject;
			if (pRes->resource_type == type && pRes->available > 0)
			{
				pResFound = pRes;
				break;
			}
		}
	}
	world.objects.restore();
	return pResFound;
}