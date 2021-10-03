#pragma once

#include "../CollectionNode.h"
#include "../Structures.h"

class SpriteResource : public CollectionNode
{
public:
	int bufferID = 0;
	Frame frame;
};