#include "BuildingBrush.h"
#include "World/World.h"
#include "World/Objects/Buildings/Buildings.h"



extern World world;

BuildingBrush::BuildingBrush()
{

}

BuildingBrush::~BuildingBrush()
{

}


void BuildingBrush::setObject(int i)
{
	if (i >= 0 && i < BUILDING_TYPES_COUNT)
		objectId = i;
}

void BuildingBrush::edit(int x, int y)
{
	switch (objectId)
	{
	case BUILDING_HOME:
		world.addObject(new Home, x, y);
		break;
	case BUILDING_BARRACKS:
		world.addObject(new Barracks, x, y);
		break;
	case BUILDING_STORE:
		world.addObject(new BuildingStore, x, y);
		break;
	case BUILDING_TOWER1:
		world.addObject(new Tower1, x, y);
		break;
	case BUILDING_CENTER:
		world.addObject(new BuildingCenter, x, y);
		break;
	case BUILDING_FARM:
		world.addObject(new BuildingFarm, x, y);
		break;
	}
}
