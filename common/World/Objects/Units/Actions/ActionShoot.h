#pragma once
#include "Action.h"
#include "../../../World.h"
#include "../Unit.h"

class ActionShoot : public Action
{
public:
	Object* target = nullptr;
	int target_x;
	int target_y;
	int counter = 0;
	int max_counter = 85;
	int shoot_time = 65;

	ActionShoot(Unit* unit);
	~ActionShoot();

	void execute();
	void set(StructAction* s);
};

