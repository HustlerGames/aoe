#include "World.h"
#include "Objects/Buildings/Barracks.h"
#include "Objects/Buildings/BuildingCenter.h"
#include "Objects/Units/Peasant.h"
#include "Objects/Units/Archer.h"
#include "Objects/Units/Swordsman.h"
#include "Objects/Projectile/Projectile.h"
#include "Objects/Simple/SimpleObject.h"
#include "Objects/Resources/Trees/Trees.h"
#include "Objects/Resources/Iron/Irons.h"
#include "Objects/Resources/Foods/Bushes.h"
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

	Peasant* peasant = new Peasant();
	peasant->player_id = 0;
	addObject(peasant, 10, 10);

	BuildingCenter* center = new BuildingCenter;
	center->player_id = 0;
	addObject(center, 14, 14);


	//юниты копьютера 

	peasant = new Peasant();
	peasant->player_id = 1;
	addObject(peasant, 30, 30);

	BuildingCenter* center = new BuildingCenter;
	center->player_id = 1;
	addObject(center, 25, 25);
}

bool World::addObject(Object* pObject, int x, int y)
{
	objects.add(pObject);
	map->placeObject(pObject, x, y);
	objects->placed();

	return true;
}

void World::removeObject(Object* pObject)
{
	// TODO: удаление с карты!
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


void World::update()
{
	int i;
	Object* pObject;


	// обновление игроков
	for (i = 0; i < PLAYER_COUNT; i++)
	{
		players[i]->update();
	}

	// обновление объектов мира
	objects.reset();
	while (pObject = objects.next())
	{
		pObject->update();
	}
}