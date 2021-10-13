#pragma once
#include "Brush.h"

class UnitBrush : public Brush
{
public:
	UnitBrush();
	~UnitBrush();
	void edit(int x, int y);
	void setObject(int i);
};