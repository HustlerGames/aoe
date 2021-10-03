#include "Editor.h"
#include "../Resources/Resources.h"
#include "../World/Constants.h"
#include "../Renderer/Renderer.h"
#include "../World/World.h"
#include <cstdlib>
#include "Brushes/TerrainBrush.h"
#include "Brushes/UnitBrush.h"
#include "Brushes/SimpleObjectBrush.h"
#include "Brushes/BuildingBrush.h"
#include "Constants.h"

extern Renderer renderer;
extern World world;

Editor::Editor() 
{
	lastPosition = { -1, -1 };

	brushes = new Brush*[NUM_BRUSHES];
	brushes[TERRAIN_BRUSH] = new TerrainBrush;
	brushes[UNIT_BRUSH] = new UnitBrush;
	brushes[OBJECT_BRUSH] = new SimpleObjectBrush;
	brushes[BUILDING_BRUSH] = new BuildingBrush;
}

Editor::~Editor()
{
	for (int i = 0; i < NUM_BRUSHES; i++)
	{
		delete brushes[i];
	}

	delete [] brushes;
}

void Editor::lMouseDown(int screenX, int screenY)
{
	//setMode(true);

	Point p = { screenX , screenY };
	WorldPosition currentPosition = renderer.screenToPos(p);
	edit(currentPosition.x, currentPosition.y);
}

void Editor::rMouseDown(int screenX, int screenY)
{
	setMode(false);
}

void Editor::lMouseUp(int screenX, int screenY)
{
	setMode(false);
}

void Editor::MouseMove(int screenX, int screenY)
{
	if (paintMode)
	{
		Point p = { screenX , screenY };
		WorldPosition currentPosition = renderer.screenToPos(p);
		edit(currentPosition.x, currentPosition.y);
	}
}



void Editor::setBrush(int brush)
{
	if (brush == TERRAIN_BRUSH || brush == UNIT_BRUSH || brush == OBJECT_BRUSH || brush == BUILDING_BRUSH)
	{
		currentBrush = brush;
	}
}

void Editor::setBrushObject(int id)
{
	return brushes[currentBrush]->setObject(id);
}

void Editor::edit(int x, int y)
{
	if (world.map->isInside(x, y))
	{
		if (x != lastPosition.x || y != lastPosition.y)
		{
			brushes[currentBrush]->edit(x, y);
			lastPosition.x = x;
			lastPosition.y = y;
		}
	}
}

void Editor::setMode(bool mode)
{
	paintMode = mode;

	if (mode == false)
	{
		lastPosition.x = -1;
		lastPosition.y = -1;
	}
}