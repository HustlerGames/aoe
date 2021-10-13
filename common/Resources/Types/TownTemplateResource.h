#pragma once

#include "../CollectionNode.h"
#include "../Structures.h"
#include "../../World/Structures.h"
#include <vector>

struct ConstructionPoint {
	int buildingType;
	int x;
	int y;
};

struct ConstructionArea {
	int buildingType;
	int left;
	int right;
	int top;
	int bottom;
};


class TownTemplateResource : public CollectionNode
{
public:
	WorldPosition center;
	std::vector<ConstructionPoint> positions;
	std::vector<ConstructionArea> areas;
};