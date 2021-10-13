#pragma once

#include "../CollectionNode.h"
#include "../Structures.h"

struct ResSpriteArray {
	Frame frames[10];
};

class StateSpriteArray : public CollectionNode
{
public:
	int bufferID = 0;

	ResSpriteArray states[10];
};