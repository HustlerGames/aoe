#pragma once

#include "Action.h"

class ActionMove : public Action
{
public:
	int targetPosX;
	int targetPosY;
	float targetX;
	float targetY;

	ActionMove(Unit* unit);
	void execute();
	void set(StructAction* s);
};
