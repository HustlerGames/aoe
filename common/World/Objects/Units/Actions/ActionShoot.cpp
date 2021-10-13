#include "ActionShoot.h"
#include "World/Constants.h"
#include "World/World.h"
#include "World/Objects/Projectile/Arrow.h"

extern World world;

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
		Arrow* pArrow = new Arrow(pUnit->position.x, pUnit->position.y, target_x, target_y);
		world.addObject(pArrow, pUnit->position.x, pUnit->position.y);

	}

	if (counter > max_counter)
	{
		completed = true;
	}

	
}

void ActionShoot::set(StructAction* s)
{
	StructActionShoot* p = (StructActionShoot*)s;
	target_x = p->coord_x;
	target_y = p->coord_y;
	start = true;
	counter = 0;
	completed = false;
}