#include <windows.h>
#include "WorldFile.h"
#include "World.h"
#include "Objects/Resources/ObjectResource.h"
#include "Objects/Units/Units.h"
#include "Objects/Buildings/Buildings.h"
#include "Objects/Resources/ResourceObjects.h"

TCHAR worldFileName[] = TEXT("d:\\projects\\testgame\\saves\\test.wsv");

extern World world;
using namespace std;


BOOL WorldFile::writeFloat(float i, HANDLE f)
{
	DWORD dwBytesWritten;
	BOOL bErrorFlag = WriteFile(
		f,
		reinterpret_cast<char*>(&i),
		sizeof(i),
		&dwBytesWritten,
		NULL
	);

	if (bErrorFlag == false)
	{
		int err = GetLastError();
		return false;
	}

	return true;
}


BOOL WorldFile::writeInt(int i, HANDLE f)
{
	DWORD dwBytesWritten;
	BOOL bErrorFlag = WriteFile(
		f,
		reinterpret_cast<char*>(&i),
		sizeof(i),
		&dwBytesWritten,
		NULL
	);

	if (bErrorFlag == false)
	{
		int err = GetLastError();
		return false;
	}
		

	return true;
}


float WorldFile::readFloat(HANDLE f)
{
	float i = 0;
	DWORD dwBytesWritten;
	BOOL bErrorFlag = ReadFile(
		f,
		reinterpret_cast<char*>(&i),
		sizeof(i),
		&dwBytesWritten,
		NULL
	);

	if (bErrorFlag == false)
		return 0;

	return i;
}



int WorldFile::readInt(HANDLE f)
{
	int i;
	DWORD dwBytesWritten;
	BOOL bErrorFlag = ReadFile(
		f,
		reinterpret_cast<char*>(&i),
		sizeof(i),
		&dwBytesWritten,
		NULL
	);

	if (bErrorFlag == false)
		return 0;

	return i;
}


bool WorldFile::read()
{
	DWORD dwBytesToWrite;
	DWORD dwBytesWritten = 0;
	BYTE* buffer;
	BOOL bErrorFlag = FALSE;

	HANDLE hFile = CreateFile(
		worldFileName,
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		0
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	int map_width = readInt(hFile);
	int map_height = readInt(hFile);

	world.map = new Map(map_width, map_height);

	for (int x = 0; x < map_width; x++)
	{
		for (int y = 0; y < map_height; y++)
		{
			Cell* cell = &world.map->cells[x][y];

			cell->terrain.type = readInt(hFile);
			cell->terrain.tile.resource_id = readInt(hFile);
			cell->terrain.tile.tile_id = readInt(hFile);

			

			TransitionList* transitions = &cell->terrain.transitions;
			int transitionCount = readInt(hFile);

			for (int i = 0; i < transitionCount; i++)
			{
				Transition* transition = new Transition;
				transition->direction = readInt(hFile);
				transition->tile.resource_id = readInt(hFile);
				transition->tile.tile_id = readInt(hFile);
				world.map->cells[x][y].terrain.transitions.add(transition);
			}

			int objectsCount = readInt(hFile);
			
			for (int n = 0; n < objectsCount; n++)
			{
				int objectType = readInt(hFile);
				float coordinate_x = readFloat(hFile);
				float coordinate_y = readFloat(hFile);
				
				if (objectType == OBJECT_TYPE_UNIT)
				{
					int unitType = readInt(hFile);

					if (unitType == UNIT_PEASANT)
					{
						Peasant* p = new Peasant;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->health = readInt(hFile);
						p->direction = readInt(hFile);
						world.addObject(p, x, y);
					}

					if (unitType == UNIT_SWORDSMAN)
					{
						Swordsman* p = new Swordsman;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->health = readInt(hFile);
						p->direction = readInt(hFile);
						world.addObject(p, x, y);
					}

					if (unitType == UNIT_ARCHER)
					{
						Archer* p = new Archer;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->health = readInt(hFile);
						p->direction = readInt(hFile);
						world.addObject(p, x, y);
					}
				}

				if (objectType == OBJECT_TYPE_BUILDING)
				{
					int buildingType = readInt(hFile);


					if (buildingType == BUILDING_BARRACKS)
					{
						Barracks* p = new Barracks;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->integrity = readInt(hFile);
						world.addObject(p, x, y);
					}

					if (buildingType == BUILDING_CENTER)
					{
						BuildingCenter* p = new BuildingCenter;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->integrity = readInt(hFile);
						world.addObject(p, x, y);
					}

					if (buildingType == BUILDING_FARM)
					{
						Barracks* p = new Barracks;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->integrity = readInt(hFile);
						world.addObject(p, x, y);
					}

					if (buildingType == BUILDING_FENCE)
					{
						Barracks* p = new Barracks;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->integrity = readInt(hFile);
						world.addObject(p, x, y);
					}

					if (buildingType == BUILDING_HOME)
					{
						Barracks* p = new Barracks;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->integrity = readInt(hFile);
						world.addObject(p, x, y);
					}

					if (buildingType == BUILDING_TOWER1)
					{
						Barracks* p = new Barracks;
						p->coordinates.x = coordinate_x;
						p->coordinates.y = coordinate_y;
						p->player_id = readInt(hFile);
						p->integrity = readInt(hFile);
						world.addObject(p, x, y);
					}
					
				}

				if (objectType == OBJECT_TYPE_RESOURCE)
				{
					int resourceType = readInt(hFile);
					int resourceID = readInt(hFile);

					if (resourceType == OBJECT_RESOURCE_TYPE_FOOD)
					{
						if (resourceID == OBJECT_RESOURCE_TYPE_FOOD_BUSH1)
						{
							Bush1* p = new Bush1;
							world.addObject(p, x, y);
						}

						if (resourceID == OBJECT_RESOURCE_TYPE_FOOD_BUSH2)
						{
							Bush2* p = new Bush2;
							world.addObject(p, x, y);
						}

						if (resourceID == OBJECT_RESOURCE_TYPE_FOOD_BUSH3)
						{
							Bush3* p = new Bush3;
							world.addObject(p, x, y);
						}
					}

					if (resourceType == OBJECT_RESOURCE_TYPE_IRON)
					{
						

						if (resourceID == OBJECT_RESOURCE_TYPE_IRON_STONE1)
						{
							Iron1* p = new Iron1;
							world.addObject(p, x, y);
						}

						if (resourceID == OBJECT_RESOURCE_TYPE_IRON_STONE2)
						{
							Iron2* p = new Iron2;
							world.addObject(p, x, y);
						}

						if (resourceID == OBJECT_RESOURCE_TYPE_IRON_STONE3)
						{
							Iron3* p = new Iron3;
							world.addObject(p, x, y);
						}
					}

					if (resourceType == OBJECT_RESOURCE_TYPE_WOOD)
					{
						if (resourceID == OBJECT_RESOURCE_TYPE_WOOD_TREE1)
						{
							Tree1* p = new Tree1;
							world.addObject(p, x, y);
						}

						if (resourceID == OBJECT_RESOURCE_TYPE_WOOD_TREE2)
						{
							Tree2* p = new Tree2;
							world.addObject(p, x, y);
						}

						if (resourceID == OBJECT_RESOURCE_TYPE_WOOD_TREE3)
						{
							Tree3* p = new Tree3;
							world.addObject(p, x, y);
						}
					}

				}
			}

			
		}
	}

	CloseHandle(hFile);
}


bool WorldFile::save()
{
	HANDLE hFile = CreateFile(
		worldFileName,
		GENERIC_WRITE,
		0,
		NULL, 
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		0
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	int map_width = world.map->getWidth();
	int map_height = world.map->getHeight();

	writeInt(map_width, hFile);
	writeInt(map_height, hFile);

	for (int x = 0; x < map_width; x++)
	{
		for (int y = 0; y < map_height; y++)
		{
			Cell* cell = &world.map->cells[x][y];

			writeInt(cell->terrain.type, hFile);
			writeInt(cell->terrain.tile.resource_id, hFile);
			writeInt(cell->terrain.tile.tile_id, hFile);
			
			TransitionList* transitions = &cell->terrain.transitions;
			int transitionCount = transitions->getLength();

			writeInt(transitionCount, hFile);

			Transition* transition;
			transitions->reset();
			while (transition = transitions->getCurrent())
			{
				writeInt(transition->direction, hFile);
				writeInt(transition->tile.resource_id, hFile);
				writeInt(transition->tile.tile_id, hFile);

				transitions->next();
			}

			writeInt(cell->Objects->length, hFile);

			cell->Objects->reset();
			while (Object* obj = cell->Objects->getCurrent())
			{
				int object_type = obj->getType();
				writeInt(object_type, hFile);
				writeFloat(obj->coordinates.x, hFile);
				writeFloat(obj->coordinates.y, hFile);

				if (object_type == OBJECT_TYPE_UNIT)
				{
					Unit* unit = dynamic_cast<Unit*>(obj);

					writeInt(unit->unit_type, hFile);
					writeInt(unit->player_id, hFile);
					writeInt(unit->health, hFile);
					writeInt(unit->direction, hFile);
				}

				if (object_type == OBJECT_TYPE_BUILDING)
				{
					Building* building = dynamic_cast<Building*>(obj);
					writeInt(building->building_type, hFile);
					writeInt(building->player_id, hFile);
					writeInt(building->integrity, hFile);
				}

				if (object_type == OBJECT_TYPE_RESOURCE)
				{
					ObjectResource* objRes = dynamic_cast<ObjectResource*>(obj);
					writeInt(objRes->resource_type, hFile);

					if (objRes->resource_type == OBJECT_RESOURCE_TYPE_FOOD)
					{
						FoodResource* h = dynamic_cast<FoodResource*>(objRes);
						writeInt(h->food_id, hFile);
					}

					if (objRes->resource_type == OBJECT_RESOURCE_TYPE_IRON)
					{
						IronResource* h = dynamic_cast<IronResource*>(objRes);
						writeInt(h->id, hFile);
					}

					if (objRes->resource_type == OBJECT_RESOURCE_TYPE_WOOD)
					{
						TreeResource* h = dynamic_cast<TreeResource*>(objRes);
						writeInt(h->id, hFile);
					}

					
				}

				cell->Objects->next();
			}
			
		}
	}

	CloseHandle(hFile);
}