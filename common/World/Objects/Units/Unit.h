#pragma once
#include "../../Constants.h"
#include "../MovableObject.h"
#include "Actions/Action.h"
#include "Tasks/Task.h"

class Action;
class Task;
struct StructAction;

class Unit : public MovableObject
{
public:
	int player_id;
	int unit_type;

	float maxHealth = 100;
	float health = 100;
	bool isDead = false;

	Action* actions[ACTION_COUNT];
	Task* tasks[TASK_TYPE_COUNT];

	WorldPosition firstLeg;
	WorldPosition lastLeg;
	
	Action* pCurrentAction = nullptr;
	Task* pCurrentTask = nullptr;
	
	Unit();
	virtual ~Unit();

	virtual void update();

	void setPosition(int x, int y);

	void setAction(StructAction* s);
	void setTask(StructTask* s);

	void stay(int time);

	void removeTask();

	int moveToObject(Object* pTarget);
	int attack(Object* pTarget);

	void takeDamage(float damage);
	void die();
	void onDeath();
protected:

	virtual Task* getDefaultTask();
	virtual Action* getDefaultAction();

	void addAction(Action* pAction);
	void addTask(Task* pTask);
};