#pragma once

#include <vector>


#define SQUAD_LEVEL_COUNT 4
#define SQUAD_LEVEL_1 0
#define SQUAD_LEVEL_2 1
#define SQUAD_LEVEL_3 2
#define SQUAD_LEVEL_4 3


struct SquadFormat
{
	int archer;
	int swordsman;
};


class Squad
{
public:
	int level = SQUAD_LEVEL_1;
	std::vector<Archer*> archers;
	std::vector<Swordsman*> swordsmans;
};