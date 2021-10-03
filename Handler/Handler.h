#pragma once

#include "../World/Objects/Object.h"




class Handler
{
public:
	Object* pSelectedObject = nullptr;
	Object* builderObject = nullptr;
	bool buildingMode = false;
	int BuildingID = 0;

	Handler();
	void onLeftClick(int x, int y);
	void onRightClick(int x, int y);
	void selectObject(Object* pObject);
	void setBuildMode(int id);
	void unselect();
};

