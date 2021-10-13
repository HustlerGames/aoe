#include "ActionMove.h"
#include "../../../Constants.h"
#include "../../../World.h"

extern World world;

ActionMove::ActionMove(Unit* unit) : Action(unit)
{
	type = ACTION_MOVE;	
}

void ActionMove::set(StructAction* s)
{
	StructActionMove* p = (StructActionMove*)s;
	targetPosX = p->pos_x;
	targetPosY = p->pos_y;

	WorldPosition pos;
	pos.x = targetPosX;
	pos.y = targetPosY;

	WorldCoordinates coords = world.map->positionCenter(pos);

	targetX = coords.x;
	targetY = coords.y;

	start = true;
	completed = false;
}

void ActionMove::execute()
{
	if (start) {
		start = false;
		pUnit->firstLeg = { targetPosX , targetPosY };
		pUnit->lastLeg = { pUnit->position.x , pUnit->position.y };
		world.map->setPass(targetPosX, targetPosY, false);
	}

	pUnit->move(targetX, targetY);

	if ((pUnit->position.x != pUnit->lastLeg.x) || (pUnit->position.y != pUnit->lastLeg.y))
	{
		world.map->setPass(pUnit->lastLeg.x, pUnit->lastLeg.y, true);
		pUnit->lastLeg = pUnit->position;
	}

	if (pUnit->coordinates.x == targetX && pUnit->coordinates.y == targetY) {
		completed = true;
	}
}