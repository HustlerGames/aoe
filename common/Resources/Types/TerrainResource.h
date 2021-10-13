#pragma once

#include "../CollectionNode.h"
#include "../Structures.h"

class TerrainResource : public CollectionNode
{
public:
	Frame tile[4];
	Frame transition[8];
	int bufferID = 0;

	TerrainResource();
	~TerrainResource();
};