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
	
	// ����� ��������� � ������ ������
	int population;
	// ��������� ���������� (�� �����)
	int avaliablePopulation;
	// ������������ ���������
	int max_population;

	// ���������� ���� ����������
	int peasands_count;


	// ������� ��� �������������
	PlayerResources unallocatedResources;
	WorkersTasksList workersTaskList;

	// ���������� ���� ��������� ��� ������������� ����������
	int available_peasands_count;

	// ����� ���������:

	// ����������� ���-�� ���������� ����������
	bool flagMinimalPopulation = false;
	// ������ ���������
	bool flagBarracksCreated = false;
	// �������� ������
	bool flagGarrisonCreated = false;
	// ����� ��������
	bool flagFenceCreated = false;
	// ����� ���������
	bool flagTowersCreated = false;
	// ������� ������ ����, ���� �� 1 �����
	bool flagExternalTroops = false;

	WorkerRequirements workerRequirements;

	// ������ �� ����� ���������
	Squad* squadGarrison = nullptr;

	// ������� �������
	SquadFormat squadFormat[SQUAD_LEVEL_COUNT];
	
	// ��������� ��������� ������
	void update();

	// �����, ����������� ������ �����
	Squad* emergingSquad = nullptr;
	// ������ ��������� �������
	std::vector<Squad*> squads;

	PlayerAI();

private:
	void doPopulationStrategy();
	int reinforcement�ode(Squad* squad);
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