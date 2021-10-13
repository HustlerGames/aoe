#include "MapEditor.h"
#include "Resources/Resources.h"
#include "World/Constants.h"
#include "Renderer/Renderer.h"
#include "World/World.h"
#include <cstdlib>
#include "Brushes/TerrainBrush.h"
#include "Brushes/UnitBrush.h"
#include "Brushes/SimpleObjectBrush.h"
#include "Brushes/BuildingBrush.h"
#include "Constants.h"

extern Renderer renderer;
extern World world;

MapEditor::MapEditor() 
{
	lastPosition = { -1, -1 };

	brushes = new Brush*[NUM_BRUSHES];
	brushes[TERRAIN_BRUSH] = new TerrainBrush;
	brushes[UNIT_BRUSH] = new UnitBrush;
	brushes[OBJECT_BRUSH] = new SimpleObjectBrush;
	brushes[BUILDING_BRUSH] = new BuildingBrush;
}

MapEditor::~MapEditor()
{
	for (int i = 0; i < NUM_BRUSHES; i++)
	{
		delete brushes[i];
	}

	delete [] brushes;
}

void MapEditor::lMouseDown(int screenX, int screenY)
{
	//setMode(true);

	
	WorldPosition currentPosition = renderer.screenToPos(screenX, screenY);
	edit(currentPosition.x, currentPosition.y);
}

void MapEditor::rMouseDown(int screenX, int screenY)
{
	setMode(false);
}

void MapEditor::lMouseUp(int screenX, int screenY)
{
	setMode(false);
}

void MapEditor::MouseMove(int screenX, int screenY)
{
	if (paintMode)
	{
		WorldPosition currentPosition = renderer.screenToPos(screenX, screenY);
		edit(currentPosition.x, currentPosition.y);
	}
}



void MapEditor::setBrush(int brush)
{
	if (brush == TERRAIN_BRUSH || brush == UNIT_BRUSH || brush == OBJECT_BRUSH || brush == BUILDING_BRUSH)
	{
		currentBrush = brush;
	}
}

void MapEditor::setBrushObject(int id)
{
	return brushes[currentBrush]->setObject(id);
}

void MapEditor::edit(int x, int y)
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

void MapEditor::setMode(bool mode)
{
	paintMode = mode;

	if (mode == false)
	{
		lastPosition.x = -1;
		lastPosition.y = -1;
	}
}