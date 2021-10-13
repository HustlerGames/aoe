#pragma once

#include "../Object.h"
#include "../../Constants.h"


class SimpleObject : public Object
{
public:
	int simple_object_id;
	SimpleObject(int id);
};

