#include "ActionDie.h"
#include "World/Constants.h"
#include "Sound/AudioSystem.h"

extern AudioSystem audio;

ActionDie::ActionDie(Unit* unit) : Action(unit)
{
	type = ACTION_DIE;
}

void ActionDie::set(StructAction* st)
{
	counter = 0;
	completed = false;
}

void ActionDie::execute()
{
	if (!pUnit->isDead)
	{
		if (++counter == max_counter)
		{
			pUnit->isDead = true;
			pUnit->onDeath();

			// нет completed, валяемся пока не почистят
		}
	}
}
