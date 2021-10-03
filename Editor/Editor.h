#pragma once

#include "../World/World.h"
#include "../World/Structures.h"
#include "../World/Constants.h"
#include "Brushes/Brush.h"
#include "Constants.h"



class Editor
{

public:
	
	bool paintMode = false;
	int currentBrush = TERRAIN_BRUSH;

	WorldPosition lastPosition;
	Brush** brushes;


	Editor();
	~Editor();
	void rMouseDown(int screenX, int screenY);
	void lMouseDown(int screenX, int screenY);
	void lMouseUp(int screenX, int screenY);
	void MouseMove(int screenX, int screenY);
	void setBrushObject(int id);
	void setBrush(int brush);
	void setMode(bool mode);
private:
	int mode = TERRAIN_BRUSH;
	void edit(int x, int y);
};

