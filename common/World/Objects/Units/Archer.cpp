
#include "Archer.h"
#include "Actions/ActionShoot.h"
#include "Tasks/TaskArcherAttack.h"
#include "Actions/ActionDie.h"

Archer::Archer()
{
	unit_type = UNIT_ARCHER;
	speed = 3;

	ActionDie* pActionDie = dynamic_cast<ActionDie*>(actions[ACTION_DIE]);
	pActionDie->max_counter = 29;

	ActionShoot* pActionShoot = new ActionShoot(this);
	pActionShoot->max_counter = 85;
	pActionShoot->shoot_time = 65;

	addTask(new TaskArcherAttack(this));
	addAction(pActionShoot);
}


void Archer::shoot(Object* pTarget)
{
	StructActionShoot st;
	st.type = ACTION_ATTACK;
	st.coord_x = pTarget->coordinates.x;
	st.coord_y = pTarget->coordinates.y;
	updateDirection(pTarget->coordinates.x - coordinates.x, pTarget->coordinates.y - coordinates.y);
	setAction(&st);
}
