#pragma once

#include "Structures.h"
#include "Task.h"
#include "../Archer.h"


class TaskArcherAttack : public Task
{
public:
	Object* pTarget = nullptr;
	TaskArcherAttack(Archer* unit);

	int execute();
	void set(StructTask* s);
};