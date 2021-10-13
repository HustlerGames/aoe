#include "World.h"
#include "Objects/Buildings/Barracks.h"
#include "Objects/Buildings/BuildingCenter.h"
#include "Objects/Units/Peasant.h"
#include "Objects/Units/Archer.h"
#include "Objects/Units/Swordsman.h"
#include "Objects/Projectile/Projectile.h"
#include "Objects/Simple/SimpleObject.h"
#include "Objects/Resources/Wood/Trees.h"
#include "Objects/Resources/Iron/Irons.h"
#include "Objects/Resources/Food/Bushes.h"
#include "Objects/Buildings/BuildingStore.h"
#include "Player/AI/PlayerAI.h"
#include "Player/LivePlayer.h"


World::World()
{	
}

World::~World(){
	removeAllObjects();
	if (map) delete map;
}

void World::LoadDefault()
{
	map = new Map(100, 100);

	// создание игроков
	LivePlayer* player = new LivePlayer;
	player->id = 0;
	player->relationship[1] = RELATION_HOSTILE;
	players[0] = player;
	player_id = 0;
	
	PlayerAI* computer = new PlayerAI;
	computer->id = 1;
	computer->relationship[0] = RELATION_HOSTILE;
	players[1] = computer;

	map = new Map(100, 100);

	// юниты игрока
	Swordsman* sw = new Swordsman();
	sw->player_id = 0;
	addObject(sw, 35, 10);

	Archer* archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 10, 10);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 12, 6);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 2, 15);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 12, 6);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 2, 15);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 6);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 7);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 8);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 13);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 14);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 15);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 16);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 17);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 23);

	archer = new Archer();
	archer->player_id = 0;
	addObject(archer, 24, 24);

	Tree1* t = new Tree1;
	addObject(t, 14, 8);

	/*BuildingCenter* center = new BuildingCenter;
	center->player_id = 0;
	addObject(center, 14, 14);
	*/

	//юниты копьютера 

	Peasant* peasant = new Peasant();
	peasant->player_id = 1;
	addObject(peasant, 15, 15);

	/*
	center = new BuildingCenter;
	center->player_id = 1;
	addObject(center, 25, 25);
	*/
}

bool World::addObject(Object* pObject, int x, int y)
{
	objects.add(pObject);
	map->placeObject(pObject, x, y);
	return true;
}

void World::removeObject(Object* pObject)
{
	map->cells[pObject->position.x][pObject->position.y].removeObject(pObject);
	objects.remove(pObject);
	delete pObject;
}

void World::removeAllObjects()
{
	Object* pObject;

	objects.reset();
	while (pObject = objects.next())
	{
		removeObject(pObject);
	}
}

void World::updateObjects()
{
	Object* pObject;
	// обновление объектов мира
	objects.reset();
	while (pObject = objects.next())
	{
		pObject->update();
	}
}

void World::clearObjects()
{
	Object* pObject;
	objects.reset();
	while (pObject = objects.next())
	{
		if (pObject->remove)
		{
			removeObject(pObject);
		}
	}
}

void World::updatePlayers()
{
	// обновление игроков
	//for (i = 0; i < PLAYER_COUNT; i++)
	//{
	//	players[i]->update();
	//}

}

void World::update()
{
	updatePlayers();
	updateObjects();
	clearObjects();
}



