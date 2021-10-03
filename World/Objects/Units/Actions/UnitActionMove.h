#pragma once

#include "../Unit.h"

class UnitActionMove : Action
{
public:
	
	UnitActionMove(Unit * pUnit);
	void execute();
};