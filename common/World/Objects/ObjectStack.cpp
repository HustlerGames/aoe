#include "ObjectStack.h"

ObjectStack::ObjectStack()
{
	pRoot = nullptr;
}

void ObjectStack::push(Object* pObject)
{
	ObjectStackItem* pItem = new ObjectStackItem;
	pItem->pObject = pObject;

	if (pRoot) {
		pItem->next = pRoot;
	}
	else {
		pItem->next = nullptr;
	}

	pRoot = pItem;
}

Object* ObjectStack::shift()
{
	if (pRoot) {

		ObjectStackItem* pItem = pRoot;
		pRoot = pItem->next;
		Object* pObject = pItem->pObject;
		delete pItem;
		return pObject;
	}

	return nullptr;


}
