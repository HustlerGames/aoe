#pragma once

#include "TransitionList.h"

class Terrain {
public:
	int type;
	Tile tile;
	TransitionList transitions;
};
