#pragma once
#include "Action.h"
#include "../../Object.h"
#include "../../Resources/ObjectResource.h"

class ActionHarvestWood : public Action
{
public:

	int counter = 0;
	int max_counter = 20;

	ObjectResource* resourceObject = nullptr;

	ActionHarvestWood(Unit* unit);
	void execute();
	void set(StructAction* st);
	void harvest();
};

