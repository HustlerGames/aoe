#include "Swordsman.h"
#include "Tasks/Tasks.h"
#include "Actions/Actions.h"

Swordsman::Swordsman()
{
	unit_type = UNIT_SWORDSMAN;
	speed = 3.5;

	ActionDie* pActionDie = dynamic_cast<ActionDie*>(actions[ACTION_DIE]);
	pActionDie->max_counter = 34;

	addTask(new TaskAttack(this));
	addAction(new ActionHit(this));
}