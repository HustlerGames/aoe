#pragma once

#include "Task.h"
#include "../../../Map/PathFinder/PathFinder.h"

class Unit;
class Task;

class TaskMove : public Task
{
public:
	int positionX;
	int positionY;
	Object* pTargetObject;
	PFPath* path;

	TaskMove(Unit* unit);
	int execute();
	void set(StructTask* s);
	bool isCorrectPath();
	PFPath* getNewPath();
	bool isTargetLeg(PFCoord* coords);
	void setMoveAction(PFCoord* coords);
	PFPath* getPath();
};