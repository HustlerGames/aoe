#pragma once
#include "Brush.h"

class SimpleObjectBrush : public Brush
{
public:
	SimpleObjectBrush();
	~SimpleObjectBrush();
	void edit(int x, int y);
	void setObject(int i);
};