#include "Swordsman.h"
#include "Tasks/Tasks.h"
#include "Actions/ActionHit.h"

Swordsman::Swordsman()
{
	unit_type = UNIT_SWORDSMAN;
	speed = 3.5;

	addTask(new TaskAttack(this));
	addAction(new ActionHit(this));
}