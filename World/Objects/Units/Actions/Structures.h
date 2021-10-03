#pragma once

#include "../../../Constants.h"
#include "../../Object.h"
#include "../../Buildings/Building.h"

struct StructAction {
	int type;
};

struct StructActionStay : StructAction{
	int time = 0;
};

struct StructActionMove : StructAction {
	int pos_x;
	int pos_y;
};


struct StructActionShoot : StructAction {
	int pos_x;
	int pos_y;
};


struct StructActionHit : StructAction {
	int pos_x;
	int pos_y;
	Object* pTarget = nullptr;
};

struct StructActionHarvestWood : StructAction {
	Object* pTarget = nullptr;
};

struct StructActionHarvestFood : StructAction {
	Object* pTarget = nullptr;
};

struct StructActionHarvestIron : StructAction {
	Object* pTarget = nullptr;
};

struct StructActionBuild : StructAction {
	Building* targetBuilding = nullptr;
};