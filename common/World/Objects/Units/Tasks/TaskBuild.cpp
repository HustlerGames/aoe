#include "TaskBuild.h"
#include "../Peasant.h"

TaskBuild::TaskBuild(Unit* unit) : Task(unit)
{
	type = TASK_TYPE_BUILD;
}

void TaskBuild::set(StructTask* s)
{
	StructTaskBuild* p = (StructTaskBuild*)s;
	pBuilding = p->pBuilding;
}

int TaskBuild::execute()
{
	if (pBuilding->integrity < pBuilding->max_integrity) {
		Peasant* peasant = (Peasant*)pUnit;
		if (peasant->distanceTo(pBuilding) < 2)
		{
			build(pBuilding);
			return TASK_STATE_OK;
		}
		else
		{
			return peasant->moveToObject(pBuilding);
		}
	}

	return TASK_STATE_CANCELLED;
}

void TaskBuild::build(Building* building)
{
	StructActionBuild st;
	st.type = ACTION_BUILD;
	st.targetBuilding = building;
	pUnit->setAction(&st);
}
