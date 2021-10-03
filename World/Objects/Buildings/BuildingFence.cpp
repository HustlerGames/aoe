#include "BuildingFence.h"
#include "../../Constants.h"
#include "../../World.h"

extern World world;

BuildingFence::BuildingFence()
{
	building_type = BUILDING_FENCE;
	width = 1;
	height = 1;
}

void BuildingFence::placed()
{
	bool fromleft = thereIsAfence(position.x - 1, position.y);
	bool fromRight = thereIsAfence(position.x + 1, position.y);
	bool fromUp = thereIsAfence(position.x, position.y - 1);
	bool fromDown = thereIsAfence(position.x , position.y + 1);

	appearence = FENCE_APPEARENCE_H;

	if (fromleft && fromRight)
	{
		if (fromUp && fromDown)
		{
			appearence = FENCE_APPEARENCE_X;
		}
		else
		{
			if (fromUp && !fromDown)
			{
				appearence = FENCE_APPEARENCE_T_DOWN;
			}
			else
			{
				appearence = FENCE_APPEARENCE_T_UP;
			}
		}

	}
	else
	{
		if (!fromleft && fromRight)
		{
			if (fromUp || fromDown)
			{
				appearence = FENCE_APPEARENCE_T_LEFT;
			}
		}

		if (fromleft && !fromRight)
		{
			if (fromUp || fromDown)
			{
				appearence = FENCE_APPEARENCE_T_RIGHT;
			}
		}
	}

	if (fromUp || fromDown)
	{
		if (!fromleft && !fromRight)
		{
			appearence = FENCE_APPEARENCE_V
		}
	}


}

bool BuildingFence::thereIsAfence(int x, int y)
{
	Objext* obj;
	CellObjectList* list = world.map->cells[x][y].Objects;
	list->reset();
	while (obj = list->next())
	{
		if (obj->getType() == OBJECT_TYPE_BUILDING)
		{
			Building* bld = (Building*)obj;
			if (bld->building_type = BUILDING_FENCE)
			{
				return true;
			}
		}
	}

	return false;
}