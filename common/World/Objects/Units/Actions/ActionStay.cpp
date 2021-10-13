#include "ActionStay.h"
#include "../../../Constants.h"

ActionStay::ActionStay(Unit* unit) : Action(unit)
{
	type = ACTION_STAY;
}

void ActionStay::set(StructAction* st)
{
	counter = 0;
	completed = false;
}

void ActionStay::execute()
{
	if(++counter == max_counter)
		completed = true;
}
