#pragma once

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
private:
	bool isZoneOccupied(int x, int y, int width, int height);
};