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

	PlayerResources* res = &world.players[player_id]->resources;

	switch (resType)
	{
	case OBJECT_RESOURCE_TYPE_IRON:
		res->iron += count;
		break;
	case OBJECT_RESOURCE_TYPE_WOOD:
		res->wood += count;
		break;
	case OBJECT_RESOURCE_TYPE_FOOD:
		res->food += count;
		break;
	}
}