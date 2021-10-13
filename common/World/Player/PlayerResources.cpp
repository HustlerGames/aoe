#include "PlayerResources.h"

PlayerResources PlayerResources::lacks()
{
	PlayerResources result;
	if (this->food < 0)
		result.food = -this->food;
	else
		result.food = 0;

	if (this->wood < 0)
		result.wood = -this->wood;
	else
		result.wood = 0;

	if (this->iron < 0)
		result.iron = -this->iron;
	else
		result.iron = 0;

	return result;
}

bool PlayerResources::enough()
{
	if (this->food < 0) return false;
	if (this->wood < 0) return false;
	if (this->iron < 0) return false;

	return true;
}