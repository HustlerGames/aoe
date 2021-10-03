#include "Building.h"
#include "../../Constants.h"

Building::Building() {
	player_id = 0;
	type = OBJECT_TYPE_BUILDING;
	building_type = BUILDING_HOME;
	state = BUILDING_STATE_READY;
}

Building::Building(int playerID, int state) {
	player_id = playerID;
	type = OBJECT_TYPE_BUILDING;
	building_type = BUILDING_HOME;
	this->state = state;
}

void Building::build(int hp)
{
	integrity += hp;
	if (integrity > max_integrity)
		integrity = max_integrity;

	if (state == BUILDING_STATE_CONSTRUCTION)
	{
		if (integrity == max_integrity)
		{
			state = BUILDING_STATE_READY;
			// EVENT?
		}

	}
}

void Building::degrade(int hp)
{
	integrity -= hp;
	if (integrity < 0)
	{
		integrity = 0;
		if (state != BUILDING_STATE_DESTROYED)
		{
			destroy();
		}
	}		
}

void Building::destroy()
{
	state = BUILDING_STATE_DESTROYED;
	// EVENT
}


bool Building::hasRunningTask(int task)
{
	return false;
}