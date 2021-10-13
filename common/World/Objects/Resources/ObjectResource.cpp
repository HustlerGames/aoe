#include "ObjectResource.h"

ObjectResource::ObjectResource()
{
	type = OBJECT_TYPE_RESOURCE;
	pass = false;
}


int ObjectResource::get(int count)
{
	if (state == OBJECT_RESOURCE_STATE_HARVEST)
	{
		int take = count;
		if (take > available) {
			take = available;
		}


		available -= take;

		if (available == 0) state = OBJECT_RESOURCE_STATE_EMPTY;

		return take;
	}

	return 0;
}