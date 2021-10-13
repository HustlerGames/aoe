#include "../../../World.h"
#include "TaskMove.h"
#include "../../../Constants.h"
#include "../Actions/Structures.h"

extern World world;

TaskMove::TaskMove(Unit* unit) : Task(unit) 
{
	type = TASK_TYPE_MOVE;
}

int TaskMove::execute()
{
	if (path = getPath())
	{
		PFCoord* nextPos = path->next();

		if (nextPos)
		{
			if (world.map->checkPass(nextPos->x, nextPos->y) == false)
			{

				// если это наша цель, мы пришли
				if (isTargetLeg(nextPos)) {
					return TASK_STATE_COMPLETED;
				}

				path = getNewPath();
				if (path == nullptr)
				{
					return TASK_STATE_CANCELLED;
				}

				nextPos = path->next();
				if(nextPos == nullptr)
					return TASK_STATE_CANCELLED;
			}

			setMoveAction(nextPos);

			return TASK_STATE_OK;
		}
	}

	return TASK_STATE_CANCELLED;
}

void TaskMove::set(StructTask* p)
{
	StructTaskMove* s = (StructTaskMove*)p;
	positionX = s->pos_x;
	positionY = s->pos_y;
	pTargetObject = s->pTargetObject;
}


bool TaskMove::isCorrectPath()
{
	if (path == nullptr) 
		return false;

	PFCoord currentPos = path->getCurrent();

	if (pUnit->position.x != currentPos.x || pUnit->position.y != currentPos.y)
		return false;

	PFCoord endPos = path->getEnd();

	if (pTargetObject)
	{
		if ( endPos.x < (pTargetObject->position.x - 1) ||
			 endPos.x > (pTargetObject->position.x + pTargetObject->width) ||
			 endPos.y < (pTargetObject->position.y - 1) ||
			 endPos.y > (pTargetObject->position.y + pTargetObject->height)
			)
		{
			return false;
		}

		return true;
	}

	if (positionX != endPos.x || positionY != endPos.y)
		return false;

	return true;
}


PFPath* TaskMove::getNewPath()
{
	PFPath* newPath = nullptr;
	
	if (pTargetObject)
	{
		int type = pTargetObject->getType();

		if (type == OBJECT_TYPE_UNIT)
		{
			Unit* unit = (Unit*)pTargetObject;
			// "тень" от юнита не даст построить путь до него, тут я убираю тень, строю путь и снова ее восстанавливаю.
			world.map->setPass(unit->lastLeg.x, unit->lastLeg.y, true);
			world.map->setPass(unit->firstLeg.x, unit->firstLeg.y, true);
			newPath = world.map->getPath(pUnit->position.x, pUnit->position.y, unit->position.x - 1, unit->position.y - 1, 3, 3);
			world.map->setPass(unit->lastLeg.x, unit->lastLeg.y, false);
			world.map->setPass(unit->firstLeg.x, unit->firstLeg.y, false);
			
		} 
		else
		{
			newPath = world.map->getPath(pUnit->position.x, pUnit->position.y, pTargetObject->position.x - 1, pTargetObject->position.y - 1, pTargetObject->width + 1, pTargetObject->height + 1);
		}
	} 
	else
	{
		newPath = world.map->getPath(pUnit->position.x, pUnit->position.y, positionX, positionY);
	}

	return newPath;
}

PFPath* TaskMove::getPath()
{
	if (isCorrectPath())
	{
		return path;
	}

	if(path)
		delete path;

	return getNewPath();
}


void TaskMove::setMoveAction(PFCoord* coords)
{
	StructActionMove st;
	st.type = ACTION_MOVE;
	st.pos_x = coords->x;
	st.pos_y = coords->y;

	pUnit->setAction(&st);
}


bool TaskMove::isTargetLeg(PFCoord* coords)
{
	if (pTargetObject && pTargetObject->getType() == OBJECT_TYPE_UNIT)
	{
		Unit* unit = (Unit*)pTargetObject;
		return (coords->x == unit->firstLeg.x && coords->y == unit->firstLeg.y ||
			coords->x == unit->lastLeg.x && coords->y == unit->lastLeg.y);
	}

	return false;
	
}