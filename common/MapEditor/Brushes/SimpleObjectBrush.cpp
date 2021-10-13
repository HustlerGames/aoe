#include "SimpleObjectBrush.h"
#include "World/World.h"
#include "World/Objects/Simple/SimpleObject.h"

extern World world;

SimpleObjectBrush::SimpleObjectBrush()
{

}

SimpleObjectBrush::~SimpleObjectBrush()
{

}


void SimpleObjectBrush::setObject(int i)
{
	if(i >= 0 && i < SIMPLE_OBJECTS_COUNT)
	objectId = i;
}

void SimpleObjectBrush::edit(int x, int y)
{
	switch (objectId)
	{
	case TREE1:
		world.addObject(new SimpleObject(TREE1), x, y);
		break;
	case GRASS01:
		world.addObject(new SimpleObject(GRASS01), x, y);
		break;
	case GRASS02:
		world.addObject(new SimpleObject(GRASS02), x, y);
		break;
	}
}