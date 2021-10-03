#pragma once
#include "Brush.h"

class TerrainBrush : public Brush
{
public:
	TerrainBrush();
	~TerrainBrush();
	void edit(int x, int y);
	void setObject(int i);
private:
	void addTransition(int x, int y, int direction, int resource_id);
};