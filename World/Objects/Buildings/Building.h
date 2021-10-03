#pragma once
#include "../Object.h"

#define BUILDING_STATE_CONSTRUCTION 1
#define BUILDING_STATE_READY 2
#define BUILDING_STATE_DESTROYED 3

class Building : public Object
{
public:
	int player_id;
	int building_type;
	int state = BUILDING_STATE_CONSTRUCTION;
	int integrity = 100;
	int max_integrity = 100;
	//Player* owner = nullptr;
	Building();
	Building(int playerID, int _state);

	void ready();
	void build(int hp);
	void degrade(int hp);
	void destroy();
	virtual bool hasRunningTask(int task_id);
};

