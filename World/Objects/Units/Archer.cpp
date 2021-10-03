
#include "Archer.h"
#include "Actions/ActionShoot.h"
#include "Tasks/TaskArcherAttack.h"

Archer::Archer()
{
	unit_type = UNIT_ARCHER;
	speed = 3;

	addTask(new TaskArcherAttack(this));
	addAction(new ActionShoot(this));
}


void Archer::shoot(Object* pTarget)
{
	StructActionShoot st;
	st.type = ACTION_ATTACK;
	st.pos_x = pTarget->position.x;
	st.pos_y = pTarget->position.y;
	setAction(&st);
}
