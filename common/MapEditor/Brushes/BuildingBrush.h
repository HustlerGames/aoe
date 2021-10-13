#pragma once
#include "Brush.h"

class BuildingBrush : public Brush
{
public:
	BuildingBrush();
	~BuildingBrush();
	void edit(int x, int y);
	void setObject(int i);
};