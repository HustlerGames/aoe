#pragma once

#include "../../Objects/Object.h"
#include "Terrain.h"
#include "CellObjectList.h"

class Object;
class CellObjectList;

class Cell {
public:
	Terrain terrain;
	bool pass = true;
	CellObjectList* Objects;

	Cell();
	~Cell();

	void addObject(Object* pObject);
	void removeObject(Object* pObject);

	Object* findObjectType(int type);
	Object* wideObject = nullptr;
};


