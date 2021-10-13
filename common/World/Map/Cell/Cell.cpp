#include "Cell.h"

Cell::Cell()
{
	Objects = new CellObjectList;
}

Cell::~Cell()
{
	delete Objects;
}

void Cell::addObject(Object* pObject)
{
	pObject->cell = this;
	Objects->add(pObject);
}
void Cell::removeObject(Object* pObject)
{
	Objects->remove(pObject);
	pObject->cell = nullptr;

}


Object* Cell::findObjectType(int type)
{
	Object* o;
	Objects->reset();
	while (o = Objects->getCurrent())
	{
		if (o->getType() == type)
		{
			return o;
		}

		Objects->next();
	}
}