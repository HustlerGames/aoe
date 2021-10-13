#pragma once

#include "World/Objects/Object.h"

struct ObjectStackItem {
	Object* pObject;
	ObjectStackItem* next;
};

class ObjectStack {

public:
	ObjectStackItem* pRoot;
	ObjectStack();
	void push(Object* pObject);
	Object* shift();
};
