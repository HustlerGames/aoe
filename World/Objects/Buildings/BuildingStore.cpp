#include "BuildingStore.h"
#include "../../Constants.h"
#include "../../World.h"

extern World world;

BuildingStore::BuildingStore()
{
	building_type = BUILDING_STORE;
	width = 2;
	height = 2;
}

void BuildingStore::put(int count, int resType)
{
	switch (resType)
	{
	case OBJECT_RESOURCE_TYPE_IRON:
		world.iron += count;
		break;
	case OBJECT_RESOURCE_TYPE_WOOD:
		world.wood += count;
		break;
	case OBJECT_RESOURCE_TYPE_FOOD:
		world.food += count;
		break;
	}
}