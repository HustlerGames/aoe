#pragma once

#include "../Player.h"
#include "TownPlanner.h"
#include <vector>
#include "Squad.h"


struct WorkersTasksList {
	Unit* buildHomes = nullptr;
	Unit* buildBarracks = nullptr;
	Unit* buildFence = nullptr;
	Unit* buildTowers = nullptr;
};


struct WorkerRequirements
{
	int harvest_food = 0;
	int harvest_wood = 0;
	int harvest_iron = 0;
	int buildHomes = 0;
	int buildBarracks = 0;
	int buildFence = 0;
	int buildTowers = 0;
};


class PlayerAI : public Player
{
public:
	

	TownPlanner townPlanner;
	
	// всего населения в данный момент
	int population;
	// доступное количество (от домов)
	int avaliablePopulation;
	// максимальное население
	int max_population;

	// количество всех поселенцев
	int peasands_count;


	// ресурсы для распределения
	PlayerResources unallocatedResources;
	WorkersTasksList workersTaskList;

	// количество всех свободных для распределения поселенцев
	int available_peasands_count;

	// Флаги состояний:

	// Минимальное кол-во поселенцев достигнуто
	bool flagMinimalPopulation = false;
	// Бараки построены
	bool flagBarracksCreated = false;
	// Гарнизон создан
	bool flagGarrisonCreated = false;
	// Забор построен
	bool flagFenceCreated = false;
	// Башни построены
	bool flagTowersCreated = false;
	// Внешние войска есть, хотя бы 1 отряд
	bool flagExternalTroops = false;

	WorkerRequirements workerRequirements;

	// ссылка на отряд гарнизона
	Squad* squadGarrison = nullptr;

	// Форматы отрядов
	SquadFormat squadFormat[SQUAD_LEVEL_COUNT];
	
	// обновляет состояние игрока
	void update();

	// новый, создающийся сейчас отряд
	Squad* emergingSquad = nullptr;
	// список атакующих отрядов
	std::vector<Squad*> squads;

	PlayerAI();

private:
	void doPopulationStrategy();
	int reinforcementСode(Squad* squad);
	bool needHomes();
	int notTooMany(int res, int numWorkers);
	int distributeWorkers(Resources resNeeded, int availableWorkers);
	void buildingBarracksStrategy();
	Resources squadCost();
	void minimalArmyStrategy();
	void applyRoutine();
	void handleNewSquad();
	void handleOuter();
	void handleArmy();
	void buildingArmyStrategy();
	void buildingTowers();
	void buildingFence();

};