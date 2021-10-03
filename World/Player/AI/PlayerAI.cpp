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
    // первый этап развития - набрать население > 10,  в приоритете создание пизанов  

    // можем ли мы сразу их создать?

    // проверяем сколько пизанов до 10 нам нужно
    int needPeasands = 10 - peasands_count;

    // создается ли поселенец?
    if (townCenter->hasRunningTask(BUILDING_TASK_CREATE_PEASANT))
    {
        // если уже создается, нам не нужно его создавать
        needPeasands--;
    }

    if (needPeasands == 0)
        return;

    // считаем сколько всего ресурсов нам надо для пизанов
    // стоимость одного
    int foodCost = 50 * needPeasands;   // 1 поселенец = 50 еды

    // таким способом мы выделяем ресурсы под задачу
    unallocatedResources.food -= foodCost;

    // хватает ли ресурсов
    if (unallocatedResources.food >= 0)
    {
        // ничего не делаем
    }
    else
    {
        int desiredCount = 0;

        // если мало - не надо отправлять всю толпу за 1 кустом     
        if (unallocatedResources.food > -30)
        {
            //нам хватит и одного
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
        // смотрим есть ли поселенец, строящий в данный момент дом 
        if (workers.buildHomes == nullptr)
        {
            // никто не строит
            // считаем сколько всего ресурсов нам надо для дома
            int woodNeed = 100;

            // выделяем
            unallocatedResources.wood -= woodNeed;

            if (unallocatedResources.wood >= 0)
            {
                // ресурсов хватает, никого не посылаем
            }
            else
            {
                // нужно послать пизана
                // если есть нераспределенные, берем оттуда
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

int PlayerAI::reinforcementСode(Squad* squad)
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
    // если кто-то уже строит бараки - ничего не делаем
    if (workers.buildBarracks)
    {
        requirements.buildBarracks = 1;
        return;
    }

    // если не строит   

    if (available_peasands_count > 0)
    {
        // есть ли ресурсы на бараки?
        Resources barracksCost = { 0,100,50 }; // 100 дерева и 50 железа на барак
        unallocatedResources -= barracksCost;

        int needWoodforBarrack = 0;
        int needIronforBarrack = 0;

        if (unallocatedResources.wood < 0)
        {
            // нужно дерево
            needWoodforBarrack = -unallocatedResources.wood;
        }

        if (unallocatedResources.iron < 0)
        {
            // нужно железо
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
        // нет свободных пизанов
        // ниче не делаем


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
    // нам нужен 1 отряд SQUAD_LEVEL_1

    // отправляем рабочих если нужно 

    // хватит ли доступных ресурсов?
    PlayerResources result = unallocatedResources - squadCost(squadsLimits[SQUAD_LEVEL_1]);
    if (result.enough())
    {
        // никаких действий не требуется
    }
    else
    {
        // отправляем рабочих
        unallocatedResources = distributeWorkers(result.getNeeded(), unallocatedResources);
    }

    if (barrack.hasRunningTask(PEASAND))
    {
        // уже кого-то делаем
    }
    else
    {
        // бараки бездействуют

        // кого нам нужно создать следующим?

        int soldier_code;

        if (minimalArmySquad == nullptr)
        {
            // пока что нет ни 1 отряда

            // создадим лучника

            soldier_code = ARCHER;
        }
        else
        {
            soldier_code = reinforcementСode(minimalArmySquad);
        }

        // есть ли ресурсы?

        PlayerResources costRes = cost[soldier_code];
        PlayerResources resRes = unallocatedResources - costRes;

        if (resRes.enough())
        {
            // добавляем в очередь задачу
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

    // некоторые поселенцы уже занимаются делом, чтобы зря их не дергать пробегаем по ним и корректируем требования
    while (pPeasand = peasandsList.first())
    {
        if (minimalArmySquad == pPeasand || buildingHome == pPeasand)
        {
            peasandsList.pop();
            continue;
        }

        if (requirements.harvest_food > 0)
        {
            if (/*пизан собирает еду*/)
            {
                requirements.harvest_food--;
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.harvest_wood > 0)
        {
            if (/*пизан собирает дерево*/)
            {
                requirements.harvest_food--;
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.harvest_iron > 0)
        {
            if (/*пизан собирает железо*/)
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
            // послать добывать еду
            requirements.harvest_food--;
            peasandsList.pop();
            continue;
        }

        if (requirements.harvest_wood)
        {
            // послать добывать дерево
            requirements.harvest_wood--;
            peasandsList.pop();
            continue;
        }

        if (requirements.harvest_iron)
        {
            // послать добывать железо
            requirements.harvest_iron--;
            peasandsList.pop();
            continue;
        }

        // отправляем строить

        if (requirements.buildBarracks)
        {
            if (workers.buildBarracks == nullptr)
            {
                // отправляем
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.buildHomes)
        {
            if (workers.buildHomes == nullptr)
            {
                // отправляем
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.buildFence)
        {
            if (workers.buildFence == nullptr)
            {
                // отправляем
                peasandsList.pop();
                continue;
            }
        }

        if (requirements.buildTowers)
        {
            if (workers.buildTowers == nullptr)
            {
                // отправляем
                peasandsList.pop();
                continue;
            }
        }


        // такого не должно быть, у нас кто-то остался!
        peasandsList.pop();
    }








}




void PlayerAI::handleNewSquad()
{
    // указатель на строящийся отряд
    if (underСonstruction)
    {
        // если отряд готов
        if (underСonstruction.ready())
        {
            if (harrison == nullptr)
            {
                // мы определяем его или в гарнизон
                harrison = underСonstruction;
            }
            else
            {
                // или во внешние войска
                outer.push(underСonstruction);
            }

            underСonstruction = nullptr;
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

            // если отряд ждет (например после создания)
            if (s->task == WAIT)
            {
                s->attack(ENEMY_BASE);
            }
        }
    }
}




void PlayerAI::handleArmy()
{
    // апгрейд отряда как задача

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
    underСonstruction.push(unit);
}
*/


void PlayerAI::update()
{

    peasands_count = peasands.size();
    available_peasands_count = peasands_count;  // все доступны изначально
    unallocatedResources = resources; // все ресурсы не распределены


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

    // применяем собранные требования
    applyRoutine();

    // управление войсками
    handleArmy();
    */
}