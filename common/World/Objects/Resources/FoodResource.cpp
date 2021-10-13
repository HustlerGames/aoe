#include "FoodResource.h"

FoodResource::FoodResource()
{
	health = 500;
	available_max = 250;
	available = 250;
	resource_type = OBJECT_RESOURCE_TYPE_FOOD;
}