#include "Map.h"
#include "../../Resources/Resources.h"

extern Resources resources;

Map::Map(int w, int h)
{
	

	pPathFinder = new PathFinder(w,h);

	width = w;
	height = h;

	cells = new Cell * [width];

	int x, y;
	for (x = 0; x < width; x++) {
		cells[x] = new Cell[height];
		for (y = 0; y < height; y++) {
			cells[x][y].terrain.tile.resource_id = GROUND_SAND;
			cells[x][y].terrain.tile.tile_id = 0;
			cells[x][y].terrain.type = GROUND_SAND;
		}
	}
}

Map::~Map()
{
	for (int x = 0; x < width; x++) {
		delete[] cells[x];
	}

	if (pPathFinder) {
		delete pPathFinder;
	}

}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}

int Map::getGround(int x, int y)
{
	return cells[x][y].terrain.type;
}


void Map::placeObject(Object* pObject, int x, int y) {

	pObject->setPosition(x, y);
	pObject->coordinates = positionCenter(pObject->position);

	setObject(pObject, x, y);
}


void Map::setObject(Object* pObject, int x, int y) {
	cells[x][y].addObject(pObject);
	bool isWide = pObject->width > 1 || pObject->height > 1;

	for (int _x = pObject->position.x; _x < (pObject->position.x + pObject->width); _x++)
	{
		for (int _y = pObject->position.y; _y < (pObject->position.y + pObject->height); _y++)
		{
			if (isWide) {
				cells[_x][_y].wideObject = pObject;
			}
			if (pObject->pass == false)
			{
				pPathFinder->setPass(_x, _y, false);
			}
			
			
		}
	}
}


PFPath* Map::getPath(int pos_x, int pos_y, int target_pos_x, int target_pos_y, int targetWidth, int targetHeight)
{
	return pPathFinder->find(pos_x, pos_y, target_pos_x, target_pos_y);
}


bool Map::checkPass(int x, int y)
{
	return pPathFinder->isPass(x, y);
}

WorldCoordinates Map::positionCenter(WorldPosition position)
{
	WorldCoordinates c;
	c.x = POSITION_SIZE * position.x + POSITION_SIZE / 2;
	c.y = POSITION_SIZE * position.y + POSITION_SIZE / 2;
	return c;
}

WorldPosition Map::positionByCoords(WorldCoordinates c) {
	WorldPosition p = { c.x / POSITION_SIZE, c.y / POSITION_SIZE };
	return p;
}

void Map::setPass(int x, int y, bool pass) 
{
	pPathFinder->setPass(x, y, pass);
}

bool Map::validPos(int x, int y)
{
	if (x < 0 || x > width || y < 0 || y > height) return false;

	return true;
}

bool Map::isInside(int x, int y)
{
	if (x < 0 || x > width || y < 0 || y > height) return false;

	return true;
}


WorldPosition Map::closestFreePositionFrom(Object* obj)
{
	WorldPosition pos = {0,0};

	int left = obj->position.x - 1;
	int top = obj->position.y - 1;
	int bottom = obj->position.y + obj->height;
	int right = obj->position.x + obj->width;
	bool found = false;
	int x, y;
	for (x = left, y = top; x < right; x++)
	{
		if (cells[x][y].pass) {
			found = true;
			break;
		}
	}
	if(!found)
		for (x = left, y = bottom; x < right; x++)
		{
			if (cells[x][y].pass) {
				found = true;
				break;
			}
		}
	if (!found)
		for (x = left, y = top; y < bottom; y++)
		{
			if (cells[x][y].pass) {
				found = true;
				break;
			}
		}
	if (!found)
		for (x = right, y = top; y < bottom; y++)
		{
			if (cells[x][y].pass) {
				found = true;
				break;
			}
		}

	if (found) {
		pos.x = x;
		pos.y = y;
	}

	return pos;
}

