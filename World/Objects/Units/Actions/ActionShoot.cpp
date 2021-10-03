#include "ActionShoot.h"
#include "../../../Constants.h"

ActionShoot::ActionShoot(Unit* unit) : Action(unit)
{
	type = ACTION_ATTACK;
}

ActionShoot::~ActionShoot()
{

}

void ActionShoot::execute()
{

	counter++;

	if (counter == shoot_time)
	{
		// shoot arrow
	}

	if (counter > max_counter)
	{
		completed = true;
	}

	
}

void ActionShoot::set(StructAction* s)
{
	StructActionShoot* p = (StructActionShoot*)s;
	target_x = p->pos_x;
	target_y = p->pos_y;
	start = true;
	counter = 0;
	completed = false;
}