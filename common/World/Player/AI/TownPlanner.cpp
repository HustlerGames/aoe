#include "TownPlanner.h"
#include "Resources/Resources.h"
#include "World/World.h"

extern World world;
extern Resources resources;

TownPlanner::TownPlanner()
{
	templatePosition = { 0,0 };
	centerPosition = { 0,0 };
}

void TownPlanner::setCenterPosition(WorldPosition pos)
{
	centerPosition = pos;

	TownTemplateResource* res = (TownTemplateResource*)resources.pRoot->get(RESOURCE_CATEGORY_TEMPLATES)->get(TOWN_TEMPLATE1);

	templatePosition = {
		pos.x - res->center.x,
		pos.y - res->center.y,
	};
}

bool TownPlanner::findBuildingPosition(int BuildingType, int sizeX, int sizeY, int &posx, int &posy)
{
	TownTemplateResource* res =  (TownTemplateResource*)resources.pRoot->get(RESOURCE_CATEGORY_TEMPLATES)->get(TOWN_TEMPLATE1);

	//ќбходим позиции, если есть такой тип здани€ и место не зан€то
	for (int i = 0; i < res->positions.size(); i++)
	{
		if (res->positions[i].buildingType == BuildingType)
		{
			if (!isZoneOccupied(posx, posy, sizeX, sizeY))
				return true;
		}
	}

	

	//ќбходим зоны, если есть такой тип здани€ провер€ем зону
	for (int i = 0; i < res->areas.size(); i++)
	{
		if (res->areas[i].buildingType == BuildingType)
		{
			// ѕроверка зоны: идем по всем позици€м слева и вниз, провер€ем от каждой позиции зону в размер здани€
			for (int x = res->areas[i].left; x < res->areas[i].right; x++)
			{
				for (int y = res->areas[i].top; y < res->areas[i].bottom; y++)
				{
					if (!isZoneOccupied(x, y, sizeX, sizeY))
						return true;
				}
			}
		}
	}

	
	return false;
}



bool TownPlanner::isZoneOccupied(int posX, int posY, int width, int height)
{
	

	int worldPosLeft = templatePosition.x + posX;
	int worldPosTop = templatePosition.y + posY;
	int worldPosRight = worldPosLeft + width;
	int worldPosBottom = worldPosTop + height;

	int worldPosX = worldPosLeft;
	int worldPosY = worldPosTop;

	for (int x = worldPosX; x < width; x++)
	{
		for (int y = posY; y < height; y++)
		{
			if (world.map->cells[x][y].pass == false || world.map->cells[x][y].wideObject)
			{
				return true;
			}
		}
	}
	
	return false;

	
}