#pragma once
#include "Structures.h"
#include "../Unit.h"

class Unit;

class Action
{
public:
	bool completed = false;
	bool start = true;
	int type;
	Unit* pUnit = nullptr;

	Action(Unit* unit);

	virtual ~Action();
	virtual void execute();
	virtual void set(StructAction* s);
	virtual void restart();
};