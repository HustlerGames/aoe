#pragma once

#include "Object.h"

class Object;

struct ObjectListItem
{
	ObjectListItem* prev = nullptr;
	ObjectListItem* next = nullptr;
	Object* pObject = nullptr;
};


class ObjectList
{
public:
	int length = 0;

	ObjectList();
	~ObjectList();

	void add(Object* pObject);
	void remove(Object* pObject);

	void reset();
	Object* next();
	void clearList();
	void save();
	void restore();

private:
	
	ObjectListItem* pRoot = nullptr;
	ObjectListItem* pPointer = nullptr;
	ObjectListItem* pSaved = nullptr;
};

