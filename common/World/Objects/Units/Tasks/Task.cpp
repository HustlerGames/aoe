#include "Task.h"

Task::Task(Unit* unit) : pUnit(unit)
{

}

Task::~Task()
{

}

int Task::execute()
{
	return TASK_STATE_OK;
}

void Task::set(StructTask* s)
{
	
}