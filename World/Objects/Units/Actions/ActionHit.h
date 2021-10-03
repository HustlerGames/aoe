#pragma once
#include "Action.h"
#include "../../Object.h"

class ActionHit : public Action
{
public:
	
	int counter = 0;
	int max_counter = 20;
	int hitTime = 15;
	
	Object* pTarget = nullptr;

	ActionHit(Unit* unit);
	void execute();
	void set(StructAction* st);
};

