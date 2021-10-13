#pragma once

#include "Unit.h"
#include "../Buildings/BuildingStore.h"

struct PeasantBag {
	int count;
	int max_count;
	int resourceType;
};

class Peasant : public Unit
{
public:
	PeasantBag bag;

	Peasant();

	void putBag(BuildingStore* pStore);
};

