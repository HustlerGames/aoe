#include "ObjectList.h"

ObjectList::ObjectList(){
}

ObjectList::~ObjectList(){

	clearList();
}

void ObjectList::clearList()
{
	ObjectListItem* temp;

	while (pRoot)
	{
		temp = pRoot;
		pRoot = pRoot->next;
		delete temp;
	}
}

void ObjectList::add(Object* pObject) {

	ObjectListItem * pItem = new ObjectListItem;
	pItem->pObject = pObject;
	pObject->pListItem = pItem;

	if (pRoot == nullptr) 
	{
		pRoot = pItem;
	}
	else
	{
		pRoot->prev = pItem;
		pItem->next = pRoot;
		pRoot = pItem;
	}

	length++;

}


void ObjectList::remove(Object* pObject) {
	
	if (pObject->pListItem->prev)	pObject->pListItem->prev->next = pObject->pListItem->next;
	if (pObject->pListItem->next)	pObject->pListItem->next->prev = pObject->pListItem->prev;
	if (pRoot == pObject->pListItem)	pRoot = pObject->pListItem->next;

	delete pObject->pListItem;
	pObject->pListItem = nullptr;

	length--;
}

void ObjectList::reset() {
	pPointer = pRoot;
}

Object* ObjectList::next() {
	
	if (pPointer)
	{
		Object* o = pPointer->pObject;
		pPointer = pPointer->next;
		return o;
	}
	
	return nullptr;
}

void ObjectList::save()
{
	pSaved = pPointer;
}

void ObjectList::restore()
{
	pPointer = pSaved;

}