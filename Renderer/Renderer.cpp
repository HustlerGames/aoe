#include "Renderer.h"
#include "../GraphicSystem/GraphicSystem.h"
#include "../World/World.h"
#include "../Resources/Resources.h"
#include "wincodec.h"
#include <math.h>
#include <string>
#include <direct.h>
#include "../World/Structures.h"
#include "Viewport.h"

#ifdef GAME_EDITOR
#include "../UI/EditorUI/GUI.h"
#else
#include "../UI/GameUI/GUI.h"
#endif


#include "../World/Map/PathFinder/PathFinder.h"
#include "../World/Objects/Units/Tasks/Tasks.h"

#define TILE_WIDTH		104.0f
#define TILE_HEIGHT		52.0f
#define SCALE_RATIO		TILE_HEIGHT / POSITION_SIZE

extern GraphicSystem GS;
extern Resources resources;
extern World world;
extern GUI gui;

Сanvas canvas;
Viewport viewport;



//---------------------



Renderer::Renderer()
{

};

Renderer::~Renderer()
{

}

void Renderer::update(int x, int y)
{
	if (x < (viewport.screen_x + 30))
	{
		viewport.move(-1, 0);
	}
	if (y < (viewport.screen_y + 30)) 
	{
		viewport.move(0, -1);
	}
	if (x > (viewport.screen_x + viewport.width - 30))
	{
		viewport.move(1, 0);
	}
	if (y > (viewport.screen_y + viewport.height - 30))
	{
		viewport.move(0, 1);
	}

}

void Renderer::initCanvas()
{
	int mapW = world.map->getWidth();
	int mapH = world.map->getHeight();
	canvas.width = (mapW + mapH) * (TILE_WIDTH / 2);
	canvas.height = (mapW + mapH) * TILE_HEIGHT / 2;
}

void Renderer::init()
{
	initCanvas();
}


void  Renderer::drawTerrain()
{
	int mapW = world.map->getWidth();
	int mapH = world.map->getWidth();

	for (int x = 0; x < mapW; x++)
	{
		for (int y = 0; y < mapH; y++)
		{
			Terrain* terrain = &world.map->cells[x][y].terrain;
			Point coords = tileCoordsByPosition(x, y);
			drawTile(coords.x, coords.y, terrain);

		}
	}
}

Sector Renderer::getSector()
{
	Sector sector;
	Point canvasCoords;
	WorldPosition worldPos;
	WorldCoordinates worldCoords;

	int mapW = world.map->getWidth();
	int mapH = world.map->getHeight();

	canvasCoords.x = viewport.x;
	canvasCoords.y = viewport.y;
	worldCoords = canvasToWorldCoords(&canvasCoords);
	worldPos.x = worldCoords.x / POSITION_SIZE;

	sector.x = worldPos.x;

	canvasCoords.x = viewport.x + viewport.width;
	canvasCoords.y = viewport.y;
	worldCoords = canvasToWorldCoords(&canvasCoords);
	worldPos.y = worldCoords.y / POSITION_SIZE;
	sector.y = worldPos.y;

	canvasCoords.x = viewport.x + viewport.width;
	canvasCoords.y = viewport.y + viewport.height;
	worldCoords = canvasToWorldCoords(&canvasCoords);
	worldPos.x = worldCoords.x / POSITION_SIZE;
	sector.right = worldPos.x;

	canvasCoords.x = viewport.x;
	canvasCoords.y = viewport.y + viewport.height;
	worldCoords = canvasToWorldCoords(&canvasCoords);
	worldPos.y = worldCoords.y / POSITION_SIZE;
	sector.bottom = worldPos.y;

	if (sector.x < 0) sector.x = 0;
	if (sector.x > mapW) sector.x = mapW;

	if (sector.y < 0) sector.y = 0;
	if (sector.y > mapH) sector.y = mapH;

	if (sector.right < 0) sector.right = 0;
	if (sector.right > mapW) sector.right = mapW;

	if (sector.bottom < 0) sector.bottom = 0;
	if (sector.bottom > mapH) sector.bottom = mapH;

	sector.width = sector.right - sector.x;
	sector.height = sector.bottom - sector.y;

	return sector;
}

void Renderer::drawObjects()
{
	
	Sector sector = getSector();

	if (sector.width > 0 && sector.height > 0)
	{
		ObjectStack stack;
		Cell** Cells =  world.map->cells;


		bool** cells = new bool* [sector.width];
		for (int k = 0; k < sector.width; k++)
		{
			cells[k] = new bool[sector.height];
			for (int l = 0; l < sector.height; l++)
			{
				cells[k][l] = false;
			}
		}

		Object* pObject = NULL;

		int pointer_x = sector.x;
		int pointer_y = sector.y;

		int current_border_x = sector.right;
		int current_border_y = sector.bottom;

		int x, y;

		// пока не перейдем на строку ниже зоны рисования
		while (pointer_y < sector.bottom) {

			// если вышли дальше рисуемой зоны по горизонтали, переход на следующую строку
			if (pointer_x >= sector.right)
			{
				pointer_x = sector.x;
				pointer_y++;
				continue;
			}

			// если ячейка уже нарисована, пропускаем
			if (cells[pointer_x - sector.x][pointer_y - sector.y]) {
				pointer_x++;
				continue;
			}



			// если стек не пуст, значит проверяем временные границы
			if (stack.pRoot) {

				if (pointer_x >= current_border_x) {
					pointer_x = sector.x;
					pointer_y++;


					if (pointer_y >= current_border_y) {

						pObject = stack.shift();
						pointer_x = pObject->position.x + pObject->width;
						pointer_y = pObject->position.y;

						drawObject(pObject);

						for (x = pObject->position.x; x < (pObject->position.x + pObject->width); x++)
						{
							for (y = pObject->position.y; y < (pObject->position.y + pObject->height); y++)
							{
								if((x - sector.x) >= 0 && (x - sector.x) < sector.width)
									if((y - sector.y) >= 0 && (y - sector.y) < sector.height)
										cells[x - sector.x][y - sector.y] = true;
							}
						}


						if (stack.pRoot) {
							current_border_x = stack.pRoot->pObject->position.x;
							current_border_y = stack.pRoot->pObject->position.y + stack.pRoot->pObject->height;
							continue;
						}
					}

					continue;
				}
			}

			// если в ячейке есть объекты рисуем их или ложим в стек
			if (Cells[pointer_x][pointer_y].Objects->length)
			{
				CellObjectList* objects = Cells[pointer_x][pointer_y].Objects;
				objects->reset();
				Object* o = objects->getCurrent();
				
				if (o->getType() == OBJECT_TYPE_BUILDING)
				{
					stack.push(o);
					current_border_x = o->position.x;
					current_border_y = o->position.y + o->height;
					pointer_x = sector.x;
					pointer_y++;
					continue;
				} 
				else
				{
					objects->sort();
					while (o = objects->getCurrent())
					{
						drawObject(o);
						objects->next();
					}

					cells[pointer_x - sector.x][pointer_y - sector.y] = true;
					pointer_x++;
					continue;
				}
			}

			

			cells[pointer_x - sector.x][pointer_y - sector.y] = true;
			pointer_x++;
		}

		for (int k = 0; k < sector.width; k++)
			delete [] cells[k];
		delete [] cells;
	}
	
}


void Renderer::render()
{
	GS.beginDraw();
	drawTerrain();
	drawMarkers();
	drawObjects();
	drawUI();
	GS.endDraw();	
}

void Renderer::drawMarkers()
{
	// draw selected unit path

	SpriteResource* spriteFoot = (SpriteResource*)resources.pRoot->get(RESOURCE_CATEGORY_GUI)->get(MARKER_FOOT);
	SpriteResource* spritePass = (SpriteResource*)resources.pRoot->get(RESOURCE_CATEGORY_GUI)->get(MARKER_PASS);
	SpriteResource* spritePath = (SpriteResource*)resources.pRoot->get(RESOURCE_CATEGORY_GUI)->get(MARKER_PATH);

	//passes

	int mapW = world.map->getWidth();
	int mapH = world.map->getHeight();

	for (int x = 0; x < mapW; x++)
	{
		for (int y = 0; y < mapH; y++)
		{
			if (world.map->checkPass(x, y) == false)
			{
				Point point = tileCenter(x,y);
				drawFrame(spritePass->bufferID, &spriteFoot->frame, point.x, point.y);
			}
		}
	}

	// foots

	Object* p;
	world.objects.reset();
	while (p = world.objects.next())
	{
		if (p->getType() == OBJECT_TYPE_UNIT)
		{
			Unit* unit = (Unit*)p;
			// draw "legs"

			Point point = tileCenter(unit->firstLeg.x, unit->firstLeg.y);
			drawFrame(spriteFoot->bufferID, &spriteFoot->frame, point.x, point.y);
			point = tileCenter(unit->lastLeg.x, unit->lastLeg.y);
			drawFrame(spriteFoot->bufferID, &spriteFoot->frame, point.x, point.y);

			// path

			if (unit->pCurrentAction->type == ACTION_MOVE)
			{
				int taskID;
				PFPath* path = nullptr;

				if (unit->pCurrentTask->type == TASK_TYPE_MOVE || unit->pCurrentTask->type == TASK_TYPE_ATTACK)
				{
					taskID = TASK_TYPE_MOVE;

					TaskMove* taskMove = (TaskMove*)unit->tasks[taskID];
					if (taskMove->path)
					{
						path = taskMove->path;
					}
				} 
				
			
				if (path) {
					PFCoord* coords;
					path->save();
					while (coords = path->next())
					{
						Point point = tileCenter(coords->x, coords->y);
						drawFrame(spritePath->bufferID, &spritePath->frame, point.x, point.y);
					}
					path->restore();
				}

			}




		}
	}

}

void Renderer::drawUI()
{
	gui.render();

	WCHAR str[] = TEXT("Добро пожаловать в TestGame!");
	GS.text(str, 100,100,1200,200);
}

void Renderer::drawTile(int x, int y, Terrain* terrain)
{
	TerrainResource* res = (TerrainResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_TERRAIN)
		->get(terrain->type);

	// main tile
	Tile* tile = &terrain->tile;
	drawToViewport(res->bufferID, res->tile[tile->tile_id].x, res->tile[tile->tile_id].y, TILE_WIDTH, TILE_HEIGHT, x, y, TILE_WIDTH, TILE_HEIGHT);

	// transitions
	TransitionList* transitions = &terrain->transitions;
	
	transitions->reset();
	while (Transition* transition = transitions->getCurrent())
	{
		TerrainResource* transitionRes = (TerrainResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_TERRAIN)
			->get(transition->tile.resource_id);

		drawToViewport(transitionRes->bufferID, transitionRes->transition[transition->direction].x, transitionRes->transition[transition->direction].y, TILE_WIDTH, TILE_HEIGHT, x, y, TILE_WIDTH, TILE_HEIGHT);
		transitions->next();
	}
}



void Renderer::drawToViewport(int bufferID, float from_X, float from_Y, float from_W, float from_H, float to_X, float to_Y, float to_W, float to_H)
{
	int x_viewport = to_X - viewport.x + viewport.screen_x;
	int y_viewport = to_Y - viewport.y + viewport.screen_y;
	int right_viewport = to_X + to_W - viewport.x + viewport.screen_x;
	int bottom_viewport = to_Y + to_H - viewport.y + viewport.screen_y;

	GS.draw(bufferID, from_X, from_Y, from_W, from_H, x_viewport, y_viewport, to_W, to_H);
}

// для отрисовки вспомогательной графики, не следует использовать для вывода объектов
Point Renderer::tileCenter(int pos_x, int pos_y)
{
	Point tileCoords = {
		(pos_x - pos_y) * TILE_WIDTH / 2 + canvas.width / 2,
		(pos_y + pos_x) * TILE_HEIGHT / 2 + TILE_HEIGHT / 2
	};
	return tileCoords;
}


void Renderer::drawBuilding(Building* pBuilding)
{
	Frame* pFrame; 
	int bufferID;

	if (pBuilding->building_type == BUILDING_FENCE)
	{
		StateSpriteResource* res = (StateSpriteResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_OBJECTS)
			->get(OBJECT_TYPE_BUILDING)
			->get(pBuilding->building_type);

		pFrame = &res->states[pBuilding->state];
		bufferID = res->bufferID;
	}
	else
	{
		StateSpriteResource* res = (StateSpriteResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_OBJECTS)
			->get(OBJECT_TYPE_BUILDING)
			->get(pBuilding->building_type);

		pFrame = &res->states[pBuilding->state];
		bufferID = res->bufferID;
	}

	WorldCoordinates coords = pBuilding->coordinates;
	Point canvasCoords = worldToCanvasCoords(&coords);

	drawFrame(bufferID, pFrame, canvasCoords.x, canvasCoords.y);
}


void Renderer::drawFrame(int bufferID, Frame* frame, float x_canvas, float y_canvas)
{
	drawToViewport(bufferID, frame->x, frame->y, frame->width, frame->height, x_canvas - frame->offset_x, y_canvas - frame->offset_y, frame->width, frame->height);
}


void Renderer::drawUnit(Unit* pUnit)
{
	int type = pUnit->unit_type;
	int action = pUnit->pCurrentAction->type;
	int direction = pUnit->direction;

	Point coordinates = worldToCanvasCoords(&pUnit->coordinates);

	if (pUnit->selected) {

		SpriteResource * s = (SpriteResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_GUI)
			->get(MARKER_SELECTED_UNIT);

		drawFrame(s->bufferID, &s->frame, coordinates.x, coordinates.y);
	}

	DirectionAnimationResource* pUnitAnimation =
		(DirectionAnimationResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_OBJECTS)
		->get(OBJECT_TYPE_UNIT)
		->get(type)->get(action);

	Frame* pFrame = pUnitAnimation->getFrame(direction, pUnit->animation_frame_counter);
	drawFrame(pUnitAnimation->bufferID, pFrame, coordinates.x, coordinates.y);

	// update counters
	pUnit->animation_pass_counter++;

	if (pUnit->animation_pass_counter >= pUnitAnimation->pass)
	{
		pUnit->animation_pass_counter = 0;
		pUnit->animation_frame_counter++;

		if (pUnit->animation_frame_counter >= pUnitAnimation->frames_count)
		{
			pUnit->animation_frame_counter = 0;
		}
	}
	
	/* draw health
	coordinates.y -= 100;
	coordinates.x -= 25;
	
	pRenderTarget->FillRectangle(
		D2D1::RectF(
			coordinates.x - viewport.x + viewport.screen_x,
			coordinates.y - viewport.y + viewport.screen_y,
			coordinates.x - viewport.x + viewport.screen_x + 50,
			coordinates.y - viewport.y + viewport.screen_y + 10),
		pBrushRed);

	pRenderTarget->FillRectangle(
		D2D1::RectF(
			coordinates.x - viewport.x + viewport.screen_x,
			coordinates.y - viewport.y + viewport.screen_y,
			coordinates.x - viewport.x + viewport.screen_x + (pUnit->health / pUnit->maxHealth * 50),
			coordinates.y - viewport.y + viewport.screen_y + 10),
		pBrushBlue);
		*/
}


void Renderer::drawObject(Object* pObject)
{
	switch(pObject->getType())
	{
	case OBJECT_TYPE_UNIT:
		drawUnit((Unit*)pObject);
		break;
	case OBJECT_TYPE_BUILDING:
		drawBuilding((Building*)pObject);
		break;
	case OBJECT_TYPE_SIMPLE:
		drawSimpleObject((SimpleObject*)pObject);
		break;
	case OBJECT_TYPE_RESOURCE:
		drawResourceObject((ObjectResource*)pObject);
		break;
	}
}

void Renderer::drawSimpleObject(SimpleObject* pObject)
{
	

	SpriteResource* res = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_OBJECTS)
		->get(OBJECT_TYPE_SIMPLE)
		->get(pObject->simple_object_id);

	Frame* pFrame = &res->frame;
	Point canvasCoords = worldToCanvasCoords(&pObject->coordinates);

	drawFrame(res->bufferID, pFrame, canvasCoords.x, canvasCoords.y);
}


void Renderer::drawResourceObject(ObjectResource* pObject)
{
	StateSpriteResource* res = (StateSpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_OBJECTS)
		->get(OBJECT_TYPE_RESOURCE)
		->get(pObject->resource_type)
		->get(pObject->id);

	Frame* pFrame = &res->states[pObject->state];
	Point canvasCoords = worldToCanvasCoords(&pObject->coordinates);

	drawFrame(res->bufferID, pFrame, canvasCoords.x, canvasCoords.y);

}

bool isInsideViewport(int screenX, int screenY)
{
	return (screenX > viewport.screen_x && 
		screenY > viewport.screen_y && 
		screenX < (viewport.screen_x + viewport.width) && 
		screenY < (viewport.screen_y + viewport.height)) ;
}



/*
* Преобразует координаты мира в координаты изометрии
*/
Point Renderer::worldToCanvasCoords(WorldCoordinates *worldCoords)
{
	float x = worldCoords->x * SCALE_RATIO;
	float y = worldCoords->y * SCALE_RATIO;

	Point canvasCoords = { 
		 x - y + canvas.width / 2, 
		(x + y) / 2 
	};

	return canvasCoords;
}

/*
* Преобразует координаты изометрии в координаты мира
*/
WorldCoordinates Renderer::canvasToWorldCoords(Point* canvasCoords)
{
	float x = canvasCoords->x - canvas.width / 2;   // смещение центра координат
	float y = 2 * canvasCoords->y;  // масштабирование по y

	// преобразование в прямоугольную систему
	WorldCoordinates worldCoords = {
		(y + x) / 2 ,
		(y - x) / 2 
	};

	// масштабирование 
	worldCoords.x /= SCALE_RATIO;
	worldCoords.y /= SCALE_RATIO;

	return worldCoords;
}


Point Renderer::tileCoordsByPosition(int pos_x, int pos_y)
{
	Point tileCoords = {
		(pos_x - pos_y)* TILE_WIDTH / 2 + canvas.width / 2 - TILE_WIDTH / 2,
		(pos_y + pos_x)* TILE_HEIGHT / 2
	};
	return tileCoords;
}


WorldPosition Renderer::screenToPos(int x, int y) 
{
	Point canvasCoords = {
		x - viewport.screen_x + viewport.x,
		y - viewport.screen_y + viewport.y
	};

	WorldCoordinates worldCoords = canvasToWorldCoords(&canvasCoords);
	WorldPosition worldPosition = { worldCoords.x / POSITION_SIZE , worldCoords.y / POSITION_SIZE };
	return worldPosition;
}

Object* Renderer::objectOnScreen(int x, int y)
{
	if (!isInsideViewport(x, y))
		return nullptr;

	Point canvasCoords = {
		x - viewport.screen_x + viewport.x,
		y - viewport.screen_y + viewport.y
	};

	WorldCoordinates worldCoords = canvasToWorldCoords(&canvasCoords);
	WorldPosition worldPosition = { worldCoords.x / POSITION_SIZE , worldCoords.y / POSITION_SIZE };

	if (!world.map->isInside(worldPosition.x, worldPosition.y))
		return nullptr;

	return world.map->cells[worldPosition.x][worldPosition.y].findObjectType(OBJECT_TYPE_UNIT);
}


//---------------------------------------





