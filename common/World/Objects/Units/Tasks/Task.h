#pragma once

#include "Structures.h"
#include "../Unit.h"

class Unit;

class Task
{
public:
	bool state;
	int type;
	Unit* pUnit = nullptr;

	Task(Unit* unit);
	virtual ~Task();
	virtual int execute();
	virtual void set(StructTask* s);
};