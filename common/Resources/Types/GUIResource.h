#pragma once

#include "../CollectionNode.h"
#include "../../Resources/Structures.h"
#include "../Constants.h"
#include "../../UI/Constants.h"


class GUIResource : public CollectionNode
{
public:
	int bufferID = 0;
	Frame frames[GUI_ELEMENTS_COUNT];
};