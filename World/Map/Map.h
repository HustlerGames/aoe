#pragma once

#include "../Objects/Object.h"
#include "PathFinder/PathFinder.h"
#include "Cell/Cell.h"
#include "../../Resources/Resources.h"




class Map {
public:
	Map(int w, int h);
	~Map();

	int getWidth();
	int getHeight();

	int getGround(int x, int y);
	void setObject(Object* pObject, int x, int y);
	void placeObject(Object* pObject, int x, int y);
	bool checkPass(int x, int y);
	PFPath* getPath(int pos_x, int pos_y, int target_pos_x, int target_pos_y, int targetWidth = 1, int targetHeight = 1);
	WorldCoordinates positionCenter(WorldPosition position);
	WorldPosition positionByCoords(WorldCoordinates c);
	void setPass(int x, int y, bool pass);
	bool validPos(int x, int y);
	bool isInside(int x, int y);
	WorldPosition closestFreePositionFrom(Object* obj);
	Cell** cells;
private:

	PathFinder* pPathFinder;

	int width;
	int height;

	
};