#pragma once

#include "../../Constants.h"
#include "../Object.h"

class ObjectResource : public Object
{
public:
	int available = 100;
	int available_max = 100;
	int health = 100;
	int resource_type = OBJECT_RESOURCE_TYPE_FOOD;
	int id;
	int state = OBJECT_RESOURCE_STATE_HARVEST;

	ObjectResource();
	int get(int count);
};