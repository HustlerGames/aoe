#pragma once

#include "Constants.h"
#include "Types/Types.h"
#include "../World/Constants.h"
#include "../UI/Constants.h"
#include "CollectionNode.h"
#include <string>
#include "tinyxml2.h"

int string_to_constant_value(const char* constant_name);

#define CONSTVAL(x) (string_to_constant_value(x))

class Resources
{
public:
	CollectionNode* pRoot = nullptr;
	Resources();
	~Resources();
	DirectionAnimationResource* loadDirAnimationRes(const char* filename);
	TerrainResource* loadTerrainRes(const char* filename);
	AnimationResource* loadAnimationRes(const char* filename);
	GUIResource* loadGUIResource(const char* filename);
	SpriteResource* loadSpriteRes(const char* filename);
	StateSpriteResource* loadStateSpriteRes(const char* filename);
	StateSpriteArray* loadStateSpriteArrayRes(const char* filename);
	TownTemplateResource* loadTownTemplateRes(const char* filename);
	bool Load(const char* filename);
private:
	void loadNodeRecursive(CollectionNode* pNode, tinyxml2::XMLElement* pElem);
};

