#include "ActionBuild.h"
#include "../../../Constants.h"
#include "../../../../Sound/AudioSystem.h"

extern AudioSystem audio;

ActionBuild::ActionBuild(Unit* unit) : Action(unit)
{
	type = ACTION_BUILD;
}

void ActionBuild::set(StructAction* st)
{
	StructActionBuild* p = (StructActionBuild*)st;
	targetBuilding = p->targetBuilding;

	counter = 0;
	completed = false;
}

void ActionBuild::execute()
{
	if (++counter == max_counter)
	{
		counter = 0;

		targetBuilding->build(10);
		audio.play(SOUND_BUILDING);
		if (targetBuilding->integrity >= targetBuilding->max_integrity)
		{
			completed = true;
		}
		
	}
}
