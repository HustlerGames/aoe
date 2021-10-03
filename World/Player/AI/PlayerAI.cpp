#include "PlayerAI.h"


PlayerAI::PlayerAI()
{

    squadFormat[SQUAD_LEVEL_1].archer = 2;
    squadFormat[SQUAD_LEVEL_1].swordsman = 2;

    squadFormat[SQUAD_LEVEL_2].archer = 3;
    squadFormat[SQUAD_LEVEL_2].swordsman = 6;

    squadFormat[SQUAD_LEVEL_3].archer = 6;
    squadFormat[SQUAD_LEVEL_3].swordsman = 8;

    squadFormat[SQUAD_LEVEL_4].archer = 10;
    squadFormat[SQUAD_LEVEL_4].swordsman = 20;

}

bool PlayerAI::needHomes()
{
    if (avaliablePopulation < max_population)
        if ((avaliablePopulation - population) < 4)
            return true;

    return false;
}


void PlayerAI::doPopulationStrategy()
{
    // ������ ���� �������� - ������� ��������� > 10,  � ���������� �������� �������  

    // ����� �� �� ����� �� �������?

    // ��������� ������� ������� �� 10 ��� �����
    int needPeasands = 10 - peasands_count;

    // ��������� �� ���������?
    if (townCenter->hasRunningTask(BUILDING_TASK_CREATE_PEASANT))
    {
        // ���� ��� ���������, ��� �� ����� ��� ���������
        needPeasands--;
    }

    if (needPeasands == 0)
        return;

    // ������� ������� ����� �������� ��� ���� ��� �������
    // ��������� ������
    int foodCost = 50 * needPeasands;   // 1 ��������� = 50 ���

    // ����� �������� �� �������� ������� ��� ������
    unallocatedResources.food -= foodCost;

    // ������� �� ��������
    if (unallocatedResources.food >= 0)
    {
        // ������ �� ������
    }
    else
    {
        int desiredCount = 0;

        // ���� ���� - �� ���� ���������� ��� ����� �� 1 ������     
        if (unallocatedResources.food > -30)
        {
            //��� ������ � ������
            desiredCount = 1;
        }
        else if (unallocatedResources.food > -200)
        {
            desiredCount = 2;
        }
        else if (unallocatedResources.food < -200)
        {
            desiredCount = available_peasands_count;
        }

        if (desiredCount > available_peasands_count)
        {
            desiredCount = available_peasands_count;
        }

        requirements.harvest_food += desiredCount;
        available_peasands_count -= desiredCount;

    }


    if (needHomes())
    {
        // ������� ���� �� ���������, �������� � ������ ������ ��� 
        if (workers.buildHomes == nullptr)
        {
            // ����� �� ������
            // ������� ������� ����� �������� ��� ���� ��� ����
            int woodNeed = 100;

            // ��������
            unallocatedResources.wood -= woodNeed;

            if (unallocatedResources.wood >= 0)
            {
                // �������� �������, ������ �� ��������
            }
            else
            {
                // ����� ������� ������
                // ���� ���� ����������������, ����� ������
                if (available_peasands_count > 0)
                {
                    available_peasands_count -= 1;
                    requirements.buildHomes = 1;
                }
                else
                {
                    if (requirements.harvest_food > 2)
                    {
                        requirements.harvest_food--;
                        requirements.buildHomes = 1;
                    }
                }
            }
        }
    }
}

int PlayerAI::reinforcement�ode(Squad* squad)
{
    SquadFormat* format = &squadFormat[squad->level];

    if (squad->archers.size() < format->archer) {
        return UNIT_ARCHER;
    }

    if (squad->swordsman.size() < format->swordsman) {
        return UNIT_SWORDSMAN;
    }

    return 0;
}

int PlayerAI::notTooMany(int res, int numWorkers)
{
    int result = 0;

    if (res < 50) result = 1;
    if (res < 100) result = 2;
    if (res < 200) result = 3;
    if (res < 500) result = 5;

    if (numWorkers < result)
        result = numWorkers;

    return result;
}



int PlayerAI::distributeWorkers(Resources resNeeded, int availableWorkers)
{
    if (availableWorkers == 0) return;

    int onWoodMax = notTooMany(resNeeded.wood, availableWorkers);
    int onIronMax = notTooMany(resNeeded.iron, availableWorkers);
    int onFoodMax = notTooMany(resNeeded.food, availableWorkers);

    int onWood = 0;
    int onIron = 0;
    int onFood = 0;

    while (availableWorkers)
    {
        if (onWoodMax > onWood)
        {
            onWood++;
            availableWorkers--;
        }

        if (availableWorkers && onIronMax > onIron)
        {
            onIron++;
            availableWorkers--;
        }

        if (availableWorkers && onFoodMax > onFood)
        {
            onFood++;
            availableWorkers--;
        }
    }

    requirements.harvest_wood += onWood;
    requirements.harvest_iron += onIron;
    requirements.harvest_food += onFood;

    return availableWorkers;
}



void PlayerAI::buildingBarracksStrategy()
{
    // ���� ���-�� ��� ������ ������ - ������ �� ������
    if (workers.buildBarracks)
    {
        requirements.buildBarracks = 1;
        return;
    }

    // ���� �� ������   

    if (available_peasands_count > 0)
    {
        // ���� �� ������� �� ������?
        Resources barracksCost = { 0,100,50 }; // 100 ������ � 50 ������ �� �����
        unallocatedResources -= barracksCost;

        int needWoodforBarrack = 0;
        int needIronforBarrack = 0;

        if (unallocatedResources.wood < 0)
        {
            // ����� ������
            needWoodforBarrack = -unallocatedResources.wood;
        }

        if (unallocatedResources.iron < 0)
        {
            // ����� ������
            needIronforBarrack = -unallocatedResources.iron;
        }


        int onWoodMax = notTooMany(needWoodforBarrack, available_peasands_count);
        int onIronMax = notTooMany(needIronforBarrack, available_peasands_count);

        int onWood = 0;
        int onIron = 0;

        while (available_peasands_count)
        {
            if (onWoodMax > onWood)
            {
                onWood++;
                available_peasands_count--;
            }



            if (available_peasands_count && onIronMax > onIron)
            {
                onIron++;
                available_peasands_count--;
            }
        }

        requirements.harvest_wood += onWood;
        requirements.harvest_iron += onIron;
    }
    else
    {
        // ��� ��������� �������
        // ���� �� ������


    }
}

PlayerAI::squadCost(int format)
{
    PlayerResources archers = UnitCost[UNIT_ARCHER] * squadFormat[format].archer;
    PlayerResources swordsmans = UnitCost[UNIT_SWORDSMAN] * squadFormat[format].swordsman;
    return archers + swordsmans;
}


void PlayerAI::minimalArmyStrategy()
{
    // ��� ����� 1 ����� SQUAD_LEVEL_1

    // ���������� ������� ���� ����� 

    // ������ �� ��������� ��������?
    PlayerResources result = unallocatedResources - squadCost(squadsLimits[SQUAD_LEVEL_1]);
    if (result.enough())
    {
        // ������� �������� �� ���������
    }
    else
    {
        // ���������� �������
        unallocatedResources = distributeWorkers(result.getNeeded(), unallocatedResources);
    }

    if (barrack.hasRunningTask(PEASAND))
    {
        // ��� ����-�� ������
    }
    else
    {
        // ������ ������������

        // ���� ��� ����� ������� ���������?

        int soldier_code;

        if (minimalArmySquad == nullptr)
        {
            // ���� ��� ��� �� 1 ������

            // �������� �������

            soldier_code = ARCHER;
        }
        else
        {
            soldier_code = reinforcement�ode(minimalArmySquad);
        }

        // ���� �� �������?

        PlayerResources costRes = cost[soldier_code];
        PlayerResources resRes = unallocatedResources - costRes;

        if (resRes.enough())
        {
            // ��������� � ������� ������
        }
        else
        {
            unallocatedResources = distributeWorkers(resRes.getNeeded(), unallocatedResources);
        }
    }
}


void PlayerAI::applyRoutine()
{

    UnitList peasandsList;
    UnitList unallocatedPeasandList;

    Unit* pPeasand;

    // ��������� ��������� ��� ���������� �����, ����� ��� �� �� ������� ��������� �� ��� � ������������ ����������
    while (pPeasand = peasandsList.first())
    {
        if (minimalArmySquad == pPeasand || buildingHome == pPeasand)
        {
            peasandsList.pop();
            continue;
        }

        if (requirements.harvest_food > 0)
        {
            if (/*����� �������� ���*/)
            {
                requirements.harvest_food--;
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.harvest_wood > 0)
        {
            if (/*����� �������� ������*/)
            {
                requirements.harvest_food--;
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.harvest_iron > 0)
        {
            if (/*����� �������� ������*/)
            {
                requirements.harvest_iron--;
                peasandsList.pop();
                continue;
            }
        }

        peasandsList.pop();
        unallocatedPeasandList.push(pPeasand);
    }

    while (pPeasand = peasandsList.first())
    {
        if (requirements.harvest_food)
        {
            // ������� �������� ���
            requirements.harvest_food--;
            peasandsList.pop();
            continue;
        }

        if (requirements.harvest_wood)
        {
            // ������� �������� ������
            requirements.harvest_wood--;
            peasandsList.pop();
            continue;
        }

        if (requirements.harvest_iron)
        {
            // ������� �������� ������
            requirements.harvest_iron--;
            peasandsList.pop();
            continue;
        }

        // ���������� �������

        if (requirements.buildBarracks)
        {
            if (workers.buildBarracks == nullptr)
            {
                // ����������
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.buildHomes)
        {
            if (workers.buildHomes == nullptr)
            {
                // ����������
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.buildFence)
        {
            if (workers.buildFence == nullptr)
            {
                // ����������
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.buildTowers)
        {
            if (workers.buildTowers == nullptr)
            {
                // ����������
                peasandsList.pop();
                continue;
            }
        }


        // ������ �� ������ ����, � ��� ���-�� �������!
        peasandsList.pop();
    }








}




void PlayerAI::handleNewSquad()
{
    // ��������� �� ���������� �����
    if (under�onstruction)
    {
        // ���� ����� �����
        if (under�onstruction.ready())
        {
            if (harrison == nullptr)
            {
                // �� ���������� ��� ��� � ��������
                harrison = under�onstruction;
            }
            else
            {
                // ��� �� ������� ������
                outer.push(under�onstruction);
            }

            under�onstruction = nullptr;
        }

    }
}

void PlayerAI::handleOuter()
{
    if (outer.size())
    {
        for (int i = 0; i < outer.size(); i++)
        {
            Squad* s = &outer[i];

            // ���� ����� ���� (�������� ����� ��������)
            if (s->task == WAIT)
            {
                s->attack(ENEMY_BASE);
            }
        }
    }
}




void PlayerAI::handleArmy()
{
    // ������� ������ ��� ������

    handleNewSquad();

    handleOuter();



}

void PlayerAI::buildingArmyStrategy()
{

}


void PlayerAI::buildingTowers()
{

}


void PlayerAI::buildingFence()
{

}

/*void eventLastInSquadDies(Squad* squad)
{
    if (minimalArmySquad == squad)
    {
        minimalArmySquad = nullptr;
        return;
    }
}
*/
/*
void eventBarracksBuilded(BuildingBarracks* barracks)
{
    there_are_barracks = true;
}
*/

/*
void eventBarracksDestroyed(BuildingBarracks* pBarracks)
{
    barracks.remove(pBarracks);

    if (barracks.size() == 0)
    {
        there_are_barracks = false;
    }

}
*/

/*
void eventSoldierCreated(Unit* unit)
{
    under�onstruction.push(unit);
}
*/


void PlayerAI::update()
{

    peasands_count = peasands.size();
    available_peasands_count = peasands_count;  // ��� �������� ����������
    unallocatedResources = resources; // ��� ������� �� ������������


    if (flagMinimalPopulation == false)
    {
        doPopulationStrategy();
    }

    /*if (there_are_barracks == false)
    {
        buildingBarracksStrategy();
    }

    if (there_are_barracks && minimal_army == false)
    {
        minimalArmyStrategy();
    }

    if (minimal_army)
    {
        buildingArmyStrategy();
    }

    if (no_towers)
    {
        buildingTowers();
    }

    if (no_fence)
    {
        buildingFence();
    }

    // ��������� ��������� ����������
    applyRoutine();

    // ���������� ��������
    handleArmy();
    */
}