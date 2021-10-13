#pragma once

#include "../CollectionNode.h"
#include "../Structures.h"

class StateSpriteResource : public CollectionNode
{
public:
	int bufferID = 0;

	Frame states[10];
};