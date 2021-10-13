#pragma once
#include "Structures.h"
#include <vector>
#include "World/Objects/Units/Peasant.h"
#include "World/Objects/Buildings/BuildingCenter.h"


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

	// ������ ������ ������
	std::vector<Unit*> units;
	// ������ ���������� ������
	std::vector<Peasant*> peasants;
	// ������ ������ ������
	std::vector<Building*> buildings;
	BuildingCenter* townCenter = nullptr;

	virtual void update();

	Player();
};