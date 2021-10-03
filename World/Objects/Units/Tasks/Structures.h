#pragma once

#include "../../Buildings/Building.h"



struct StructTask {
	int type;
};

struct StructTaskStay : StructTask {
	
};

struct StructTaskMove : StructTask {
	int pos_x;
	int pos_y;
	Object* pTargetObject = nullptr;
};

struct StructTaskAttack : StructTask {
	Object* target;
};

struct StructTaskMoveToUnit : StructTask {
	Object* target;
};

struct StructTaskHarvest : StructTask {
	Object* resourceObject;
};

struct StructTaskBuild : StructTask {
	Building* pBuilding = nullptr;
};