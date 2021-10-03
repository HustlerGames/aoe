#pragma once
#include "Constants.h"
#include "Map/Map.h"
#include "Objects/Object.h"
#include <string>
#include "Player/Player.h"
#include "Objects/ObjectList.h"

class World
{
public:
	ObjectList objects;
	Map* map = nullptr;

	int player_id;
	Player* players[PLAYER_COUNT];

	World();
	~World();

	bool addObject(Object* object, int x, int y);
	void removeObject(Object* pObject);
	void removeAllObjects();
	void LoadDefault();
	void update();
	//bool Load(const char* filename);
	//bool Save(const char* filename);
	//void clear();


	
private:


};