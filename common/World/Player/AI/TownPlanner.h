#pragma once

#include "World/Structures.h"

/*
* Планировщик города
*/
class TownPlanner
{
public:
	WorldPosition templatePosition;
	WorldPosition centerPosition;

	TownPlanner();

	bool findBuildingPosition(int BuildingType, int sizeX, int sizeY, int &posx, int &posy);
	void setCenterPosition(WorldPosition pos);
private:
	bool isZoneOccupied(int posX, int posY, int width, int height);
};