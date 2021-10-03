#include "TaskArcherAttack.h"
#include "../../../Constants.h"


TaskArcherAttack::TaskArcherAttack(Archer* unit) : Task(unit)
{
	type = TASK_TYPE_ATTACK;
}

int TaskArcherAttack::execute()
{
	if (pUnit->distanceTo(pTarget) < 10)
	{
		((Archer*)pUnit)->shoot(pTarget);
		return TASK_STATE_OK;
	}
	else
		return pUnit->moveToObject(pTarget);
}

void TaskArcherAttack::set(StructTask* s)
{
	StructTaskAttack* p = (StructTaskAttack*)s;
	pTarget = p->target;
}