#include "Sidebar.h"
#include "SimpleObjectsList.h"
#include "TerrainList.h"
#include "UnitsList.h"
#include "BuildingsList.h"


Sidebar::Sidebar()
{
	position.left = 40;
	position.top = 40;
	position.right = 740;
	position.bottom = 840;

	add(new SimpleObjectsList);
	add(new TerrainList);
	add(new UnitsList);
	add(new BuildingsList);
}

Sidebar::~Sidebar()
{

}