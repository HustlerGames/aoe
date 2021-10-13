#include "UnitBrush.h"
#include "World/World.h"
#include "World/Objects/Units/Peasant.h"
#include "World/Objects/Units/Swordsman.h"
#include "World/Objects/Units/Archer.h"

extern World world;

UnitBrush::UnitBrush()
{

}

UnitBrush::~UnitBrush()
{

}


void UnitBrush::setObject(int i)
{
	if(i >= 0 && i < UNIT_TYPE_COUNT)
		objectId = i;
}

void UnitBrush::edit(int x, int y)
{
	switch (objectId)
	{
	case UNIT_PEASANT:
		world.addObject(new Peasant, x, y);
		break;
	case UNIT_SWORDSMAN:
		world.addObject(new Swordsman, x, y);
		break;
	case UNIT_ARCHER:
		world.addObject(new Archer, x, y);
		break;
	}
}
