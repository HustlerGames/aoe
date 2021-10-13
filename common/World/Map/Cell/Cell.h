#pragma once

#include "World/Objects/Object.h"
#include "Terrain.h"
#include "CellObjectList.h"
#include <vector>

class Object;
class CellObjectList;

class Cell {
public:
	Terrain terrain;
	bool pass = true;
	CellObjectList* Objects;
	std::vector<Object*>lowObjects;

	Cell();
	~Cell();

	void addObject(Object* pObject);
	void removeObject(Object* pObject);

	Object* findObjectType(int type);
	Object* wideObject = nullptr;
};


