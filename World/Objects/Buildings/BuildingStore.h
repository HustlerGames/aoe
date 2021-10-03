#pragma once
#include "Building.h"

class BuildingStore : public Building
{
public:
	BuildingStore();

	void put(int count, int resType);
};
