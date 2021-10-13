#include "ActionHit.h"

ActionHit::ActionHit(Unit* unit) : Action(unit)
{
	type = ACTION_ATTACK;
}

void ActionHit::execute()
{
	counter++;

	if (counter == hitTime)
	{
		pTarget->takeDamage(200);
	}

	if (counter > max_counter)
		completed = true;
}

void ActionHit::set(StructAction* st)
{
	StructActionHit* str = (StructActionHit*)st;
	pTarget = str->pTarget;
	counter = 0;
}