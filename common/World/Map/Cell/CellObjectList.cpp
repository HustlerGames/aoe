#include "CellObjectList.h"

void CellObjectList::reset()
{
	current = root;
}

Object* CellObjectList::next()
{
	if (current) {
		current = current->cellListItemRight;
	}

	return current;
}


Object* CellObjectList::getCurrent()
{
	return current;
}

int min(Object* a, Object* b)
{
	int aVal = a->position.x + a->position.y;
	int bVal = b->position.x + b->position.y;


	if (aVal == bVal) return 0;
	if (aVal > bVal) return 1;
	return -1;	
}

void CellObjectList::add(Object* object)
{
	if (root == nullptr) {
		root = object;
	}
	else
	{
		root->cellListItemLeft = object;
		object->cellListItemRight = root;
		root = object;
	}

	current = root;

	length++;
}
void CellObjectList::remove(Object* object)
{
	if (root == object)
	{
		root = object->cellListItemRight;
	}

	if (current == object)
	{
		current = object->cellListItemRight;
	}

	if (object->cellListItemLeft)
		object->cellListItemLeft->cellListItemRight = object->cellListItemRight;

	if (object->cellListItemRight) 
		object->cellListItemRight->cellListItemLeft = object->cellListItemLeft;


	object->cellListItemRight = nullptr;
	object->cellListItemLeft = nullptr;

	length--;

}


inline void CellObjectList::swap(Object* a, Object* b)
{
	if (a && b) {

		Object* aPrev = a->cellListItemLeft;
		Object* aNext = a->cellListItemRight;
		Object* bPrev = b->cellListItemLeft;
		Object* bNext = b->cellListItemRight;

		if (aNext == b)
		{
			b->cellListItemLeft = aPrev;
			b->cellListItemRight = a;
			a->cellListItemRight = bNext;
			a->cellListItemLeft = b;
			if (aPrev) aPrev->cellListItemRight = b;
			if (bNext) bNext->cellListItemLeft = a;
		} 
		else if (bNext == a)
		{
			a->cellListItemLeft = bPrev;
			a->cellListItemRight = b;
			b->cellListItemLeft = a;
			b->cellListItemRight = aNext;
			if (bPrev) bPrev->cellListItemRight = a;
			if (aNext) aNext->cellListItemLeft = b;
		}
		else 
		{
			a->cellListItemLeft = bPrev;
			a->cellListItemRight = bNext;
			b->cellListItemLeft = aPrev;
			b->cellListItemRight = aNext;
			if (bPrev) bPrev->cellListItemRight = a;
			if (bNext) bNext->cellListItemLeft = a;
			if (aNext) aNext->cellListItemLeft = b;
			if (aPrev) aPrev->cellListItemRight = b;
		}

		if (a == root)
			root = b;
		else if (b == root)
			root = a;
	}	
}



void CellObjectList::sort()
{


	if (length < 2) return;

	Object* start = root;
	Object* p = start;
	Object* minimal = start;

	while (start)
	{
		p = start;
		minimal = start;

		while (p)
		{
			if (min(p, minimal) < 0) 
				minimal = p;

			p = p->cellListItemRight;
		}

		if(minimal != start)
			swap(minimal, start);

		start = minimal->cellListItemRight;
	}
}

