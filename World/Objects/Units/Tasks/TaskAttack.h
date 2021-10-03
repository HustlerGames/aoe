#pragma once

#include "Task.h"
#include "../../Object.h"
#include "Structures.h"

class Task;

class TaskAttack : public Task
{
public:
	Object* pTarget = nullptr;
	TaskAttack(Unit* unit);
	int execute();
	void set(StructTask* s);
};