#include "TaskStay.h"
#include "../../../Constants.h"

TaskStay::TaskStay(Unit* unit) : Task(unit)
{
	type = TASK_TYPE_STAY;
}

int TaskStay::execute()
{
	StructAction st;
	st.type = ACTION_STAY;
	pUnit->setAction(&st);
	return TASK_STATE_OK;
}

void TaskStay::set(StructTask* s)
{
	
}