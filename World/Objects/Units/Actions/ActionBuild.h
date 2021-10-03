#pragma once
#include "Action.h"
#include "../../Buildings/Building.h"

class ActionBuild : public Action
{
public:

	int counter = 0;
	int max_counter = 100;

	Building* targetBuilding = nullptr;

	ActionBuild(Unit* unit);
	void execute();
	void set(StructAction* st);
};

