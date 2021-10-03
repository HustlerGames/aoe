#include "TerrainBrush.h"
#include "../../World/World.h"

extern World world;
extern Resources resources;

TerrainBrush::TerrainBrush()
{
	objectId = GROUND_SAND;
}

TerrainBrush::~TerrainBrush()
{

}

void TerrainBrush::setObject(int i)
{
	if (i >= 0 && i < GROUND_TYPE_COUNT)
		objectId = i;
}

void TerrainBrush::addTransition(int x, int y, int direction, int resource_id)
{
	if (world.map->isInside(x, y)) {
		Transition* pTransition = new Transition;
		pTransition->direction = direction;
		pTransition->tile.resource_id = resource_id;
		pTransition->tile.tile_id = 0;

		world.map->cells[x][y].terrain.transitions.add(pTransition);
	}
}

void TerrainBrush::edit(int x, int y)
{
	TerrainResource* tr = (TerrainResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_TERRAIN)
		->get(objectId);

	int tileCount = 1;
	int tile_id = 0;//rand() % tileCount;

	world.map->cells[x][y].terrain.type = objectId;
	world.map->cells[x][y].terrain.tile.resource_id = objectId;
	world.map->cells[x][y].terrain.tile.tile_id = tile_id;
	world.map->cells[x][y].terrain.transitions.clear();

	addTransition(x, y - 1, DIRECTION_UP, objectId);
	addTransition(x + 1, y - 1, DIRECTION_UP_RIGHT, objectId);
	addTransition(x + 1, y, DIRECTION_RIGHT, objectId);
	addTransition(x + 1, y + 1, DIRECTION_DOWN_RIGHT, objectId);
	addTransition(x, y + 1, DIRECTION_DOWN, objectId);
	addTransition(x - 1, y + 1, DIRECTION_DOWN_LEFT, objectId);
	addTransition(x - 1, y, DIRECTION_LEFT, objectId);
	addTransition(x - 1, y - 1, DIRECTION_UP_LEFT, objectId);
}
