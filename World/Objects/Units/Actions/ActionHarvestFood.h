#pragma once
#include "Action.h"
#include "../../Object.h"
#include "../../Resources/ObjectResource.h"

class ActionHarvestFood : public Action
{
public:

	int counter = 0;
	int max_counter = 20;

	ObjectResource* resourceObject = nullptr;

	ActionHarvestFood(Unit* unit);
	void execute();
	void set(StructAction* st);
	void harvest();
};

