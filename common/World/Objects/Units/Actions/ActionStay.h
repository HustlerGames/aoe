#pragma once

#include "Action.h"
#include "../Unit.h"

class ActionStay : public Action
{
public:
	int counter = 0;
	int max_counter = 10;

	ActionStay(Unit* unit);
	void set(StructAction* st);
	void execute();
};

