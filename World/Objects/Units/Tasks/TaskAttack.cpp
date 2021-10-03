#include "TaskAttack.h"
#include "../../../Constants.h"


TaskAttack::TaskAttack(Unit* unit) : Task(unit)
{
	type = TASK_TYPE_ATTACK;
}

int TaskAttack::execute()
{
	if (pUnit->distanceTo(pTarget) < 2)
	{
		StructActionHit st;
		st.type = ACTION_ATTACK;
		st.pTarget = pTarget;
		pUnit->setAction(&st);

		return TASK_STATE_OK;
	}
	else
	{
		if (pUnit->moveToObject(pTarget) != TASK_STATE_OK)
		{
			pUnit->stay(10);
		}
	}
}

void TaskAttack::set(StructTask* s)
{
	StructTaskAttack* p = (StructTaskAttack*)s;
	pTarget = p->target;
}