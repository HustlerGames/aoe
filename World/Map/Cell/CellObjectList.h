#pragma once

#include "../../Objects/Object.h"

class Object;

class CellObjectList {
public:
	int length = 0;
	bool sorted = false;
	void add(Object* object);
	void remove(Object* object);
	void sort();
	Object* next();
	void reset();
	Object* getCurrent();
private:
	Object* current = nullptr;
	Object* root = nullptr;

	inline void swap(Object* a, Object* b);
};

