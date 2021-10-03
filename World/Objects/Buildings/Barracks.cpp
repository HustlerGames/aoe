#include "Barracks.h"
#include "../../Constants.h"
#include "../../World.h"
#include "../Units/Units.h"
#include "BuildingTaskList.h"
#include "BuildingTaskIDs.h"

extern World world;

Barracks::Barracks()
{
	building_type = BUILDING_BARRACKS;
	width = 4;
	height = 4;
}

void Barracks::update()
{
	updateTasks();
}

bool Barracks::addTask(int task_id, int quantity = 1)
{
	switch (task_id)
	{
	case BUILDING_TASK_CREATE_ARCHER:

		if (tasks.root->id == BUILDING_TASK_CREATE_ARCHER)
		{
			tasks.root->quantity += quantity;
		}
		else
		{
			BuildingTask* task = new BuildingTask;
			task->id = BUILDING_TASK_CREATE_ARCHER;
			task->duration = 100;
			task->quantity = 1;
			task->counter = 0;
			tasks.add(task);
		}
		
		return true;

	case BUILDING_TASK_CREATE_SWORDSMAN:
		

		if (tasks.root->id == BUILDING_TASK_CREATE_SWORDSMAN)
		{
			tasks.root->quantity += quantity;
		}
		else
		{
			BuildingTask* task = new BuildingTask;
			task->id = BUILDING_TASK_CREATE_SWORDSMAN;
			task->duration = 150;
			task->quantity = quantity;
			task->counter = 0;
			tasks.add(task);
		}

		

		return true;
	}

	return false;
}


bool Barracks::executeTask(int task_id)
{
	switch (task_id)
	{
	case BUILDING_TASK_CREATE_ARCHER:
		return createArcher();
	case BUILDING_TASK_CREATE_SWORDSMAN:
		return createSwordsman();
	}

	return false;


}


bool Barracks::createArcher()
{
	WorldPosition wp = world.map->closestFreePositionFrom(this);

	Archer* archer = new Archer;
	archer->player_id = this->player_id;
	world.addObject(archer, wp.x, wp.y);
}


bool Barracks::createSwordsman()
{
	WorldPosition wp = world.map->closestFreePositionFrom(this);

	Swordsman* swordsman = new Swordsman;
	swordsman->player_id = this->player_id;
	world.addObject(swordsman, wp.x, wp.y);
}