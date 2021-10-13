#pragma once
#include "Action.h"
#include "../../Object.h"

class ActionDie : public Action
{
public:

	int counter = 0;
	int max_counter = 20;

	ActionDie(Unit* unit);
	void execute();
	void set(StructAction* st);
};

