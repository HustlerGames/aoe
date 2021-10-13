#pragma once
#include "Action.h"
#include "../../Object.h"
#include "../../Resources/ObjectResource.h"

class ActionHarvestIron : public Action
{
public:

	int counter = 0;
	int max_counter = 50;

	ObjectResource* resourceObject = nullptr;

	ActionHarvestIron(Unit* unit);
	void execute();
	void set(StructAction* st);
	void harvest();
};

