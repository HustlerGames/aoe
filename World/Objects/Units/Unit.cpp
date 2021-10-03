#include "Unit.h"
#include <math.h>
#include "Actions/Actions.h"
#include "../../World.h"
#include "Tasks/Tasks.h"

extern World world;

#define PROCESS_WALK 1

Unit::Unit()
{
	type = OBJECT_TYPE_UNIT;

	addAction(new ActionStay(this));
	addAction(new ActionMove(this));
	addTask(new TaskStay(this));
	addTask(new TaskMove(this));

	pCurrentTask = getDefaultTask();

	speed = 5;
}



Unit::~Unit()
{
	for (int i = 0; i < ACTION_COUNT; i++)
	{
		if (actions[i]) delete actions[i];
	}

	for (int i = 0; i < TASK_TYPE_COUNT; i++)
	{
		if (tasks[i]) delete tasks[i];
	}
}


void Unit::setAction(StructAction* s)
{
	if (actions[s->type] == nullptr) 
		return;
		
	if (pCurrentAction && (s->type != pCurrentAction->type)) {
		animation_pass_counter = 0;
		animation_frame_counter = 0;
	}

	pCurrentAction = actions[s->type];
	pCurrentAction->set(s);
}

void Unit::setTask(StructTask* s)
{
	if (tasks[s->type] == nullptr)
		return;

	pCurrentTask = tasks[s->type];
	pCurrentTask->set(s);
}

void Unit::addTask(Task* pTask)
{
	if (tasks[pTask->type])
	{
		delete tasks[pTask->type];
	}

	tasks[pTask->type] = pTask;
}

void Unit::addAction(Action* pAction)
{
	if (actions[pAction->type])
	{
		delete actions[pAction->type];
	}

	actions[pAction->type] = pAction;
}


void Unit::update()
{
	if (pCurrentAction == nullptr || pCurrentAction->completed)
	{
		if (pCurrentTask->execute() != TASK_STATE_OK )
		{
			pCurrentTask = getDefaultTask();
			pCurrentTask->execute();
		}
	}

	pCurrentAction->execute();	
}

Action* Unit::getDefaultAction()
{
	return actions[ACTION_STAY];
}

Task* Unit::getDefaultTask()
{
	return tasks[TASK_TYPE_STAY];
}


void Unit::removeTask()
{
	pCurrentTask = nullptr;
}


int Unit::moveToObject(Object* pTarget)
{
	StructTaskMove st;
	st.pTargetObject = pTarget;
	tasks[TASK_TYPE_MOVE]->set(&st);
	return tasks[TASK_TYPE_MOVE]->execute();	
}

int Unit::attack(Object* pTarget)
{
	StructTaskAttack str;
	str.target = pTarget;
	tasks[TASK_TYPE_ATTACK]->set(&str);
	return tasks[TASK_TYPE_ATTACK]->execute();
}

void Unit::stay(int time)
{
	StructActionStay st;
	st.type = ACTION_STAY;
	st.time = time;

	setAction(&st);
}

void Unit::setPosition(int x, int y)
{
	position = { x, y };
	lastLeg = position;
	firstLeg = position;
}