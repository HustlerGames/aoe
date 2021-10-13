#pragma once
#include "../Constants.h"
#include "../Structures.h"
#include "../Map/Cell/Cell.h"
#include "ObjectList.h"

struct ObjectListItem;
class ObjectList;
class Cell;

/*
 * ����� ������ ����, ������� ����� ���� ���������.
 * �������� ���������� � �������, ������� � ����, ������ ��� �������.
 */
class Object
{
public:
	// ������� ����� ��������
	int width = 0;
	int height = 0;
	bool remove = false;
	bool pass = true;
	bool canBeDamaged = false;
	bool selected = false;

	WorldPosition position;
	WorldCoordinates coordinates;
	

	//�������� ��������
	int animation_frame_counter = 0;
	int animation_pass_counter = 0;
	
	Object();
	virtual ~Object();

	int getType();
	virtual void update();
	virtual void setPosition(int x, int y);

	ObjectListItem* pListItem = nullptr;

	Cell* cell = nullptr;
	Object* cellListItemLeft = nullptr;
	Object* cellListItemRight = nullptr;
	Object* cellLowListItemLeft = nullptr;
	Object* cellLowListItemRight = nullptr;

	float distanceTo(Object* pTarget);

	virtual void takeDamage(float damage);



protected:
	int type;
};