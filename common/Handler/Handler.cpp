#include "Handler.h"
#include "Renderer/Renderer.h"
#include "UI/GameUI/GameUI.h"
#include "World/Objects/Buildings/Buildings.h"
#include "Sound/AudioSystem.h"


extern Renderer renderer;
extern World world;
extern GameUI gui;
extern AudioSystem audio;

Handler::Handler() {

}

void Handler::setBuildMode(int id)
{
	buildingMode = true;
	BuildingID = id;
}


void Handler::onLeftClick(int x, int y)
{
	if (buildingMode)
	{
		if (pSelectedObject)
		{
			WorldPosition pos = renderer.screenToPos(x, y);

			if (BuildingID == BUILDING_BARRACKS) {
				Barracks* barracks = new Barracks;
				barracks->state = BUILDING_STATE_CONSTRUCTION;
				barracks->integrity = 1;
				world.addObject(barracks, pos.x, pos.y);

				StructTaskBuild st;
				st.type = TASK_TYPE_BUILD;
				st.pBuilding = barracks;
				((Unit*)pSelectedObject)->setTask(&st);

				audio.play(SOUND_BUILD);
			}
			/*
			//if (BuildingID == BUILDING_CENTER) world.addObject(new Center, pos.x, pos.y);
			if (BuildingID == BUILDING_HOME) {
				Home* home = new Home;
				home->state = BUILDING_STATE_CONSTRUCTION;
				home->integrity = 1;
				world.addObject(home, pos.x, pos.y);
			}

			if (BuildingID == BUILDING_STORE) {
				BuildingStore* store = new BuildingStore;
				store->state = BUILDING_STATE_CONSTRUCTION;
				store->integrity = 1;
				world.addObject(store, pos.x, pos.y);


			}
			*/


			
		}

		buildingMode = false;
		BuildingID = 0;
		builderObject = nullptr;
		
	}


	Object* p = renderer.objectOnScreen(x, y);

	if (p == nullptr)
	{
		unselect();
	}
	else
	{
		if (p->getType() == OBJECT_TYPE_UNIT)
		{
			selectObject(p);
		}
	}
}

void Handler::onRightClick(int x, int y) {
	if (pSelectedObject) {
		WorldPosition pos = renderer.screenToPos( x,y );
		if (world.map->isInside(pos.x, pos.y))
		{
			Object* unit = world.map->cells[pos.x][pos.y].findObjectType(OBJECT_TYPE_UNIT);
			if (unit) {
				StructTaskAttack st;
				st.type = TASK_TYPE_ATTACK;
				st.target = unit;
				((Unit*)pSelectedObject)->setTask(&st);
				return;
			}

			
			ObjectResource* objResource = (ObjectResource*)world.map->cells[pos.x][pos.y].findObjectType(OBJECT_TYPE_RESOURCE);
			if (objResource)
			{
				if (pSelectedObject->getType() == OBJECT_TYPE_UNIT)
				{
					Unit* unitObj = (Unit*)pSelectedObject;
					if (unitObj->unit_type == UNIT_PEASANT)
					{
						StructTaskHarvest st;
						st.type = TASK_TYPE_HARVEST;
						st.resourceObject = objResource;
						unitObj->setTask(&st);
						return;
					}
				}
			}



			if(world.map->checkPass(pos.x, pos.y))
			{
				StructTaskMove st;
				st.type = TASK_TYPE_MOVE;
				st.pos_x = pos.x;
				st.pos_y = pos.y;

				Unit* unit = (Unit*)pSelectedObject;
				unit->setTask(&st);
			}
		}
	}
}


void Handler::selectObject(Object* pObject)
{
	if (pSelectedObject) {
		pSelectedObject->selected = false;
	}
	pSelectedObject = pObject;
	pSelectedObject->selected = true;

	gui.panel->SetObject(pSelectedObject);
}

void Handler::unselect()
{
	if (pSelectedObject) {
		pSelectedObject->selected = false;
		pSelectedObject = nullptr;
		gui.panel->SetObject(nullptr);
	}
}