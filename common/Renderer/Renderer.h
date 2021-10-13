#pragma once

#include "World/World.h"
#include "Resources/Resources.h"
#include "World/Objects/ObjectStack.h"
#include "World/Objects/Units/Unit.h"
#include "World/Objects/Buildings/Building.h"
#include "World/Objects/Buildings/BuildingFence.h"
#include "World/Objects/Simple/SimpleObject.h"
#include "World/Objects/Resources/ObjectResource.h"
#include <string>
#include "Structures.h"
#include "UI/GUI.h"
#include "World/Objects/Projectile/Projectile.h"

class Renderer
{
public:

	GUI* gui = nullptr;

	int terrainSurfID;
	int markerSurfID;

	std::string appPath;
	std::string resPath;

	Renderer();
	~Renderer();
	void init();
	void update(int x, int y);
	void render();
	void drawUI();

	Object* objectOnScreen(int x, int y);


	Point worldToCanvasCoords(WorldCoordinates* worldCoords);
	WorldCoordinates canvasToWorldCoords(Point* canvasCoords);
	Point tileCoordsByPosition(int pos_x, int pos_y);
	WorldPosition screenToPos(int x, int y);
	Point tileCenter(int pos_x, int pos_y);

private:
	
	void initCanvas();
	void drawTerrain();
	
	Sector getSector();

	void drawObject(Object* pObject);
	void drawBuilding(Building* pObject);
	void drawFence(BuildingFence* pFence);
	void drawSimpleObject(SimpleObject* pObject);
	void drawResourceObject(ObjectResource* pObject);
	void drawProjectileObject(Projectile* pObject);
	void drawHealth(Object* obj);

	void drawUnit(Unit* pUnit);
	void drawFrame(int bufferID, Frame* frame, float x, float y);
	void drawToViewport(int bufferID, float from_X, float from_Y, float from_W, float from_H, float to_X, float to_Y, float to_W, float to_H);
	void drawTile(int x, int y, Terrain* terrain);
	void drawLowObjects();

	void drawMarkers();
	void  drawObjects();
};