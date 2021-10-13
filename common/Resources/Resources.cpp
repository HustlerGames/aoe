#include "Resources.h"
#include "../GraphicSystem/GraphicSystem.h"
#include <cstring>
#include "../World/Objects/Buildings/Building.h"
#include <direct.h>

#define TILE_WIDTH  105.0f
#define TILE_HEIGHT  53.0f

extern GraphicSystem GS;

char workingDirectory[MAX_PATH];
char resourcePath[MAX_PATH];

struct TranslationElement
{

	const char* string;
	int value;
} translations[] = {
	{ "GROUND_WATER", GROUND_WATER },
	{ "GROUND_WATER2", GROUND_WATER2 },
	{ "GROUND_WATER3", GROUND_WATER3 },
	{ "GROUND_STONE1", GROUND_STONE1 },
	{ "GROUND_GRASS", GROUND_GRASS },
	{ "GROUND_GRASS1", GROUND_GRASS1 },
	{ "GROUND_GRASS2", GROUND_GRASS2 },
	{ "GROUND_GRASS3", GROUND_GRASS3 },
	{ "GROUND_SAND", GROUND_SAND },
	{ "GROUND_SAND1", GROUND_SAND1 },
	{ "GROUND_DUST1", GROUND_DUST1 },
	{ "OBJECT_TYPE_SIMPLE", OBJECT_TYPE_SIMPLE },
	{ "OBJECT_TYPE_BUILDING", OBJECT_TYPE_BUILDING },
	{ "OBJECT_TYPE_UNIT", OBJECT_TYPE_UNIT },
	{ "OBJECT_TYPE_PROJECTILE", OBJECT_TYPE_PROJECTILE },
	{ "DIRECTION_UP", DIRECTION_UP },
	{ "DIRECTION_UP_RIGHT", DIRECTION_UP_RIGHT },
	{ "DIRECTION_RIGHT", DIRECTION_RIGHT },
	{ "DIRECTION_DOWN_RIGHT", DIRECTION_DOWN_RIGHT },
	{ "DIRECTION_DOWN", DIRECTION_DOWN },
	{ "DIRECTION_DOWN_LEFT", DIRECTION_DOWN_LEFT },
	{ "DIRECTION_LEFT", DIRECTION_LEFT },
	{ "DIRECTION_UP_LEFT", DIRECTION_UP_LEFT },
	{ "UNIT_PEASANT", UNIT_PEASANT },
	{ "UNIT_SWORDSMAN", UNIT_SWORDSMAN },
	{ "UNIT_ARCHER", UNIT_ARCHER },
	{ "ACTION_STAY", ACTION_STAY },
	{ "ACTION_MOVE", ACTION_MOVE },
	{ "ACTION_HIT", ACTION_HIT },
	{ "ACTION_SHOOT", ACTION_SHOOT },
	{ "RESOURCE_TYPE_TERRAIN", RESOURCE_TYPE_TERRAIN },
	{ "RESOURCE_TYPE_SPRITE", RESOURCE_TYPE_SPRITE },
	{ "RESOURCE_TYPE_ANIMATION", RESOURCE_TYPE_ANIMATION },
	{ "RESOURCE_TYPE_DIRECT_ANIMATION", RESOURCE_TYPE_DIRECT_ANIMATION },
	{ "RESOURCE_CATEGORY_TERRAIN", RESOURCE_CATEGORY_TERRAIN },
	{ "RESOURCE_CATEGORY_OBJECTS", RESOURCE_CATEGORY_OBJECTS },
	{ "RESOURCE_GUI_ONE", RESOURCE_GUI_ONE },
	{ "GUI_BUTTONSLIST_SCROLL_UP", GUI_BUTTONSLIST_SCROLL_UP },
	{ "GUI_BUTTONSLIST_SCROLL_DOWN", GUI_BUTTONSLIST_SCROLL_DOWN },
	{ "RESOURCE_CATEGORY_GUI", RESOURCE_CATEGORY_GUI },
	{ "RESOURCE_TYPE_GUI", RESOURCE_TYPE_GUI },
	{ "BUILDING_HOME", BUILDING_HOME },
	{ "BUILDING_FARM", BUILDING_FARM },
	{ "BUILDING_BARRACKS", BUILDING_BARRACKS },
	{ "GRASS01", GRASS01 },
	{ "GRASS02", GRASS02 },
	{ "BUILDING_STORE", BUILDING_STORE },
	{ "BUILDING_TOWER1", BUILDING_TOWER1 },
	{ "ACTION_DIE", ACTION_DIE },
	{ "ACTION_ATTACK", ACTION_ATTACK },
	{ "ACTION_HARVEST_WOOD", ACTION_HARVEST_WOOD },
	{ "ACTION_HARVEST_IRON", ACTION_HARVEST_IRON },
	{ "ACTION_HARVEST_FOOD", ACTION_HARVEST_FOOD },
	{ "ACTION_HARVEST_BUILD", ACTION_HARVEST_BUILD },
	{ "ACTION_BUILD", ACTION_BUILD },
	{ "MARKER_SELECTED_UNIT", MARKER_SELECTED_UNIT },
	{ "MARKER_PATH", MARKER_PATH },
	{ "MARKER_FOOT", MARKER_FOOT },
	{ "MARKER_PASS", MARKER_PASS },
	{ "OBJECT_RESOURCE_TYPE_FOOD", OBJECT_RESOURCE_TYPE_FOOD },
	{ "OBJECT_RESOURCE_TYPE_IRON", OBJECT_RESOURCE_TYPE_IRON },
	{ "OBJECT_RESOURCE_TYPE_WOOD", OBJECT_RESOURCE_TYPE_WOOD },
	{ "OBJECT_RESOURCE_TYPE_WOOD_TREE1", OBJECT_RESOURCE_TYPE_WOOD_TREE1 },
	{ "OBJECT_RESOURCE_TYPE_WOOD_TREE2", OBJECT_RESOURCE_TYPE_WOOD_TREE2 },
	{ "OBJECT_RESOURCE_TYPE_WOOD_TREE3", OBJECT_RESOURCE_TYPE_WOOD_TREE3 },
	{ "OBJECT_RESOURCE_TYPE_FOOD_BUSH1", OBJECT_RESOURCE_TYPE_FOOD_BUSH1 },
	{ "OBJECT_RESOURCE_TYPE_FOOD_BUSH2", OBJECT_RESOURCE_TYPE_FOOD_BUSH2 },
	{ "OBJECT_RESOURCE_TYPE_FOOD_BUSH3", OBJECT_RESOURCE_TYPE_FOOD_BUSH3 },
	{ "OBJECT_RESOURCE_TYPE_IRON_STONE1", OBJECT_RESOURCE_TYPE_IRON_STONE1 },
	{ "OBJECT_RESOURCE_TYPE_IRON_STONE2", OBJECT_RESOURCE_TYPE_IRON_STONE2 },
	{ "OBJECT_RESOURCE_TYPE_IRON_STONE3", OBJECT_RESOURCE_TYPE_IRON_STONE3 },
	{ "OBJECT_RESOURCE_STATE_HARVEST", OBJECT_RESOURCE_STATE_HARVEST },
	{ "OBJECT_RESOURCE_STATE_EMPTY", OBJECT_RESOURCE_STATE_EMPTY },
	{ "OBJECT_TYPE_RESOURCE", OBJECT_TYPE_RESOURCE },
	{ "RESOURCE_TYPE_STATE_SPRITE", RESOURCE_TYPE_STATE_SPRITE },
	{ "RESOURCE_GUI_PANEL", RESOURCE_GUI_PANEL },
	{ "RESOURCE_GUI_HEADER", RESOURCE_GUI_HEADER },
	{ "RESOURCE_GUI_MAP", RESOURCE_GUI_MAP },
	{ "RESOURCE_GUI_PREVIEW", RESOURCE_GUI_PREVIEW },
	{ "RESOURCE_GUI_COMMANDS", RESOURCE_GUI_COMMANDS },
	{ "RESOURCE_GUI_BUILDING_TASKS", RESOURCE_GUI_BUILDING_TASKS },
	{ "RESOURCE_GUI_BUILDING_TASKS_QUEUE", RESOURCE_GUI_BUILDING_TASKS_QUEUE },
	{ "RESOURCE_GUI_CURSOR", RESOURCE_GUI_CURSOR },
	{ "RESOURCE_GUI_CURSOR_ATTACK", RESOURCE_GUI_CURSOR_ATTACK },
	{ "RESOURCE_GUI_CURSOR_BUILD", RESOURCE_GUI_CURSOR_BUILD },
	{ "RESOURCE_GUI_CURSOR_MOVE", RESOURCE_GUI_CURSOR_MOVE },
	{ "RESOURCE_GUI_MENU", RESOURCE_GUI_MENU },
	{ "RESOURCE_GUI_MENU_BUTTON_CLOSE", RESOURCE_GUI_MENU_BUTTON_CLOSE },
	{ "RESOURCE_GUI_MENU_BUTTON_SAVE", RESOURCE_GUI_MENU_BUTTON_SAVE },
	{ "RESOURCE_GUI_MENU_BUTTON_LOAD", RESOURCE_GUI_MENU_BUTTON_LOAD },
	{ "RESOURCE_GUI_MENU_BUTTON_SETTINGS", RESOURCE_GUI_MENU_BUTTON_SETTINGS },
	{ "RESOURCE_GUI_MENU_BUTTON_QUIT", RESOURCE_GUI_MENU_BUTTON_QUIT },
	{ "RESOURCE_GUI_MINIMAP", RESOURCE_GUI_MINIMAP },
	{ "RESOURCE_GUI_OPEN_MENU_BUTTON", RESOURCE_GUI_OPEN_MENU_BUTTON },
	{ "BUILDING_CENTER", BUILDING_CENTER },
	{ "BUILDING_FENCE", BUILDING_FENCE },
	{ "BUILDING_TASK_CREATE_ARCHER", BUILDING_TASK_CREATE_ARCHER },
	{ "BUILDING_TASK_CREATE_SWORDSMAN", BUILDING_TASK_CREATE_SWORDSMAN },
	{ "BUILDING_TASK_CREATE_PEASANT", BUILDING_TASK_CREATE_PEASANT },
	{ "PEASANT_TASK_CREATE_BARRACKS", PEASANT_TASK_CREATE_BARRACKS },
	{ "PEASANT_TASK_CREATE_CENTER", PEASANT_TASK_CREATE_CENTER },
	{ "PEASANT_TASK_CREATE_TOWER", PEASANT_TASK_CREATE_TOWER },
	{ "PEASANT_TASK_CREATE_STORE", PEASANT_TASK_CREATE_STORE },
	{ "PEASANT_TASK_CREATE_HOME", PEASANT_TASK_CREATE_HOME },
	{ "PEASANT_TASK_CREATE_FENCE", PEASANT_TASK_CREATE_FENCE },
	{ "BUILDING_STATE_CONSTRUCTION", BUILDING_STATE_CONSTRUCTION },
	{ "BUILDING_STATE_READY", BUILDING_STATE_READY },
	{ "BUILDING_STATE_DESTROYED", BUILDING_STATE_DESTROYED },
	{ "FENCE_APPEARENCE_H", FENCE_APPEARENCE_H },
	{ "FENCE_APPEARENCE_V", FENCE_APPEARENCE_V },
	{ "FENCE_APPEARENCE_X", FENCE_APPEARENCE_X },
	{ "FENCE_APPEARENCE_T_UP", FENCE_APPEARENCE_T_UP },
	{ "FENCE_APPEARENCE_T_RIGHT", FENCE_APPEARENCE_T_RIGHT },
	{ "FENCE_APPEARENCE_T_DOWN", FENCE_APPEARENCE_T_DOWN },
	{ "FENCE_APPEARENCE_T_LEFT", FENCE_APPEARENCE_T_LEFT },
	{ "RESOURCE_TYPE_STATE_SPRITE_ARRAY", RESOURCE_TYPE_STATE_SPRITE_ARRAY },
	{ "TOWN_TEMPLATE1", TOWN_TEMPLATE1 },
	{ "RESOURCE_CATEGORY_TEMPLATES", RESOURCE_CATEGORY_TEMPLATES },
	{ "PROJECTILE_TYPE_ARROW", PROJECTILE_TYPE_ARROW },

	{ "TREE1", TREE1 }
};

int string_to_constant_value(const char* constant_name)
{
	if (constant_name == nullptr)
	{
		int f = 0;
	}

	int count = sizeof(translations) / sizeof(TranslationElement);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(translations[i].string, constant_name) == 0) {
			return translations[i].value;
		}
	}

	return -1;
}



DirectionAnimationResource* Resources::loadDirAnimationRes(const char* filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	tinyxml2::XMLElement* pElem = doc.FirstChildElement("Frames");
	int cols = pElem->IntAttribute("cols");
	int rows = pElem->IntAttribute("rows");
	int speed = pElem->IntAttribute("speed");
	int pass = pElem->IntAttribute("pass");

	DirectionAnimationResource* pDAnimation = new DirectionAnimationResource(rows, cols);

	pDAnimation->speed = speed;
	pDAnimation->pass = pass;

	tinyxml2::XMLElement* current = pElem->FirstChildElement("Frame");

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			pDAnimation->setFrame(
				row,
				col,
				current->IntAttribute("X"),
				current->IntAttribute("Y"),
				current->IntAttribute("Width"),
				current->IntAttribute("Height"),
				current->IntAttribute("OffsetX"),
				current->IntAttribute("OffsetY")
			);

			current = current->NextSiblingElement();
		}
	}

	int length = strlen(filename);
	char bitmapFileName[MAX_PATH] = "";
	strcpy_s(bitmapFileName, MAX_PATH, filename);
	bitmapFileName[length - 3] = 'p';
	bitmapFileName[length - 2] = 'n';
	bitmapFileName[length - 1] = 'g';


	pDAnimation->bufferID = GS.createSurfaceFromFile(bitmapFileName);


	return pDAnimation;
}

int countChildren(tinyxml2::XMLElement* pElem)
{
	int count = 0;
	for (tinyxml2::XMLNode* child = pElem->FirstChild(); child; child = child->NextSibling()) count++;
	return count;
}

Resources::Resources() 
{
	_getcwd(workingDirectory, MAX_PATH);
	strcat_s(resourcePath, MAX_PATH, workingDirectory);
	strcat_s(resourcePath, MAX_PATH, "\\..\\data\\");
}

Resources::~Resources()
{
	if (pRoot)
		delete pRoot;
}


void parseFrame(Frame* frame, tinyxml2::XMLElement* frameNode)
{
	frame->x = frameNode->IntAttribute("x");
	frame->y = frameNode->IntAttribute("y");
	frame->width = frameNode->IntAttribute("width");
	frame->height = frameNode->IntAttribute("height");
	frame->offset_x = frameNode->IntAttribute("offsetX");
	frame->offset_y = frameNode->IntAttribute("offsetY");
}


SpriteResource* Resources::loadSpriteRes(const char* filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	tinyxml2::XMLElement* pRootElem = doc.FirstChildElement("RESOURCE");
	tinyxml2::XMLElement* pFrameElem = pRootElem->FirstChildElement();

	SpriteResource* pSpriteRes = new SpriteResource;
	parseFrame(&pSpriteRes->frame, pFrameElem);
	
	int length = strlen(filename);
	char bitmapFileName[MAX_PATH] = "";
	strcpy_s(bitmapFileName, MAX_PATH, filename);
	bitmapFileName[length - 3] = 'p';
	bitmapFileName[length - 2] = 'n';
	bitmapFileName[length - 1] = 'g';
	
	
	pSpriteRes->bufferID = GS.createSurfaceFromFile(bitmapFileName);


	return pSpriteRes;
}




StateSpriteArray* Resources::loadStateSpriteArrayRes(const char* filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
	
	tinyxml2::XMLElement* pRootElem = doc.FirstChildElement("RESOURCE");

	StateSpriteArray* pSpriteStateRes = new StateSpriteArray;

	for (tinyxml2::XMLElement* stateElem = pRootElem->FirstChildElement("STATE"); stateElem; stateElem = stateElem->NextSiblingElement())
	{
		int state_id = CONSTVAL(stateElem->Attribute("id"));
		for (tinyxml2::XMLElement* appearenceElem = stateElem->FirstChildElement("APPEARENCE"); appearenceElem; appearenceElem = appearenceElem->NextSiblingElement())
		{
			int frame_id = CONSTVAL(appearenceElem->Attribute("id"));
			tinyxml2::XMLElement* frameElem = appearenceElem->FirstChildElement("FRAME");
			
			parseFrame(&pSpriteStateRes->states[state_id].frames[frame_id], frameElem);
			
		}
	}

	int length = strlen(filename);
	char bitmapFileName[MAX_PATH] = "";
	strcpy_s(bitmapFileName, MAX_PATH, filename);
	bitmapFileName[length - 3] = 'p';
	bitmapFileName[length - 2] = 'n';
	bitmapFileName[length - 1] = 'g';

	pSpriteStateRes->bufferID = GS.createSurfaceFromFile(bitmapFileName);
	return pSpriteStateRes;
}



StateSpriteResource* Resources::loadStateSpriteRes(const char* filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	tinyxml2::XMLElement* pRootElem = doc.FirstChildElement("RESOURCE");

	StateSpriteResource* pSpriteStateRes = new StateSpriteResource;
	

	for (tinyxml2::XMLElement* stateElem = pRootElem->FirstChildElement(); stateElem; stateElem = stateElem->NextSiblingElement())
	{
		int id = CONSTVAL(stateElem->Attribute("id"));
		tinyxml2::XMLElement* pFrameElem = stateElem->FirstChildElement();
		parseFrame(&pSpriteStateRes->states[id], pFrameElem);
	}

	int length = strlen(filename);
	char bitmapFileName[MAX_PATH] = "";
	strcpy_s(bitmapFileName, MAX_PATH, filename);
	bitmapFileName[length - 3] = 'p';
	bitmapFileName[length - 2] = 'n';
	bitmapFileName[length - 1] = 'g';


	pSpriteStateRes->bufferID = GS.createSurfaceFromFile(bitmapFileName);


	return pSpriteStateRes;
}




TerrainResource* Resources::loadTerrainRes(const char* filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	tinyxml2::XMLElement* pRoot = doc.FirstChildElement("RESOURCE");
	tinyxml2::XMLElement* pElemProperties = pRoot->FirstChildElement("PROPERTIES");
	tinyxml2::XMLElement* pElemTiles = pRoot->FirstChildElement("TILES");
	tinyxml2::XMLElement* pElemTransitions = pRoot->FirstChildElement("TRANSITIONS");

	TerrainResource* res = new TerrainResource();

	tinyxml2::XMLElement* current = pElemTiles->FirstChildElement();

	int i = 0;
	for (tinyxml2::XMLElement* current = pElemTiles->FirstChildElement(); current; current = current->NextSiblingElement(), i++)
	{
		res->tile[i].x = current->IntAttribute("x");
		res->tile[i].y = current->IntAttribute("y");
		res->tile[i].width = TILE_WIDTH;
		res->tile[i].height = TILE_HEIGHT;
		res->tile[i].offset_x = 0;
		res->tile[i].offset_y = 0;
	}
	
	for (current = pElemTransitions->FirstChildElement(), i = 0; current; current = current->NextSiblingElement(), i++)
	{
		res->transition[i].x = current->IntAttribute("x");
		res->transition[i].y = current->IntAttribute("y");
		res->transition[i].width = TILE_WIDTH;
		res->transition[i].height = TILE_HEIGHT;
		res->transition[i].offset_x = 0;
		res->transition[i].offset_y = 0;
	}

	int length = strlen(filename);
	char bitmapFileName[MAX_PATH] = "";
	strcpy_s(bitmapFileName, MAX_PATH, filename);
	bitmapFileName[length - 3] = 'p';
	bitmapFileName[length - 2] = 'n';
	bitmapFileName[length - 1] = 'g';

	res->bufferID = GS.createSurfaceFromFile(bitmapFileName);

	return res;
}

AnimationResource* Resources::loadAnimationRes(const char* filename)
{
	return nullptr;
}

void Resources::loadNodeRecursive(CollectionNode* pNode, tinyxml2::XMLElement* pElem)
{
	

	for (tinyxml2::XMLElement* child = pElem->FirstChildElement(); child; child = child->NextSiblingElement())
	{
		const char* k = child->Attribute("id");

		int id = CONSTVAL(child->Attribute("id"));
		
		if (strcmp(child->Name(), "CATEGORY") == 0)
		{
			int length = 60;// countChildren(child);
			CollectionNode* pNewNode = new CollectionNode(length);
			pNode->add(id, pNewNode);
			loadNodeRecursive(pNewNode, child);
		}

		if (strcmp(child->Name(), "RESOURCE") == 0)
		{
			int type = CONSTVAL(child->Attribute("type"));
			const char* filename = child->Attribute("file");
			char fullname[MAX_PATH] = "";
			strcat_s(fullname, MAX_PATH, resourcePath);
			strcat_s(fullname, MAX_PATH, filename);

			CollectionNode* node = nullptr;

			switch (type)
			{
				case RESOURCE_TYPE_ANIMATION:
					node = loadAnimationRes(fullname);
					break;
				case RESOURCE_TYPE_TERRAIN:				
					node = loadTerrainRes(fullname);
					break;
				case RESOURCE_TYPE_DIRECT_ANIMATION:
					node = loadDirAnimationRes(fullname);
					break;
				case RESOURCE_TYPE_GUI:
					node = loadGUIResource(fullname);
					break;
				case RESOURCE_TYPE_SPRITE:
					node = loadSpriteRes(fullname);
					break;
				case RESOURCE_TYPE_STATE_SPRITE:
					node = loadStateSpriteRes(fullname);
					break;
				case RESOURCE_TYPE_STATE_SPRITE_ARRAY:
					node = loadStateSpriteArrayRes(fullname);
					break;
			}

			if (node)
				pNode->add(id, node);
		}
	}
}

TownTemplateResource* loadTownTemplateRes(const char* filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	TownTemplateResource* res = new TownTemplateResource;

	tinyxml2::XMLElement* pRootElem = doc.FirstChildElement("RESOURCE");
	tinyxml2::XMLElement* pPositionsElem = pRootElem->FirstChildElement("POSITIONS");
	tinyxml2::XMLElement* pAreasElem = pRootElem->FirstChildElement("AREAS");
	tinyxml2::XMLElement* pCenterElem = pRootElem->FirstChildElement("CENTER_POSITION");

	res->center = {
		pCenterElem->IntAttribute("X"),
		pCenterElem->IntAttribute("Y")
	};

	for (tinyxml2::XMLElement* position = pPositionsElem->FirstChildElement(); position; position = position->NextSiblingElement())
	{
		ConstructionPoint p = {
			position->IntAttribute("BUILDING_TYPE"),
			position->IntAttribute("X"),
			position->IntAttribute("Y")
		};

		res->positions.push_back(p);
	}

	for (tinyxml2::XMLElement* area = pAreasElem->FirstChildElement(); area; area = area->NextSiblingElement())
	{
		ConstructionArea a = {
			area->IntAttribute("BUILDING_TYPE"),
			area->IntAttribute("LEFT"),
			area->IntAttribute("RIGHT"),
			area->IntAttribute("TOP"),
			area->IntAttribute("BOTTOM")
		};

		res->areas.push_back(a);
	}

	return res;
}


GUIResource* Resources::loadGUIResource(const char* filename) 
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	GUIResource* res = new GUIResource;

	tinyxml2::XMLElement* pRootElem = doc.FirstChildElement("RESOURCE");
	tinyxml2::XMLElement* pFramesElem = pRootElem->FirstChildElement("FRAMES");
	int i = 0;
	for (tinyxml2::XMLElement* child = pFramesElem->FirstChildElement(); child; child = child->NextSiblingElement(), i++)
	{
		res->frames[i].x = child->IntAttribute("x");
		res->frames[i].y = child->IntAttribute("y");
		res->frames[i].width = child->IntAttribute("width");
		res->frames[i].height = child->IntAttribute("height");
		res->frames[i].offset_x = 0;
		res->frames[i].offset_y = 0;
	}

	int length = strlen(filename);
	char bitmapFileName[MAX_PATH] = "";
	strcpy_s(bitmapFileName, MAX_PATH, filename);
	bitmapFileName[length - 3] = 'p';
	bitmapFileName[length - 2] = 'n';
	bitmapFileName[length - 1] = 'g';

	res->bufferID = GS.createSurfaceFromFile(bitmapFileName);

	return res;
}

bool Resources::Load(const char* filename)
{
	char fullname[MAX_PATH] = "";
	strcat_s(fullname, MAX_PATH, resourcePath);
	strcat_s(fullname, MAX_PATH, filename);

	tinyxml2::XMLDocument doc;
	doc.LoadFile(fullname);
	tinyxml2::XMLElement* pElem = doc.FirstChildElement("RESOURCES");
	int length = countChildren(pElem);
	pRoot = new CollectionNode(length);
	loadNodeRecursive(pRoot, pElem);

	return true;
}