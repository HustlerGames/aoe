#pragma once
#include "../Objects/Units/Peasant.h"
#include "Structures.h"



struct PlayerResources
{
	int iron;
	int wood;
	int food;
};


class Player
{
public:

	int id;

	unsigned int max_population;
	unsigned int population;
	
	int relationship[PLAYER_COUNT];

	PlayerResources resources;

	PlayerResources UnitCost[UNIT_TYPE_COUNT];

	// список юнитов игрока
	std::vector<Unit*> units;
	// список поселенцев игрока
	std::vector<Peasant*> peasants;
	// список зданий игрока
	std::vector<Building*> buildings;

	BuildingCenter* townCenter = nullptr;

	virtual void update();

	Player();
};