#pragma once

#include "Building.h"

class BuildingFence : public Building
{
public:
	int appearence = FENCE_APPEARENCE_H;
	BuildingFence();
	void updateAppearence();
	bool thereIsAfence(int x, int y);
};

