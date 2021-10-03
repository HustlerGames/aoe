#include "UnitsList.h"
#include "../../World/Constants.h"
#include "../Controls/ButtonsList.h"
#include "../../Editor/Editor.h"

extern Resources resources;
extern Editor editor;

void ulOnItemChanged(int i)
{
	editor.setBrush(UNIT_BRUSH);
	editor.setBrushObject(i);
}


UnitsList::UnitsList()
{
	position.left = 40 + 10 + 122 + 10 + 122 + 10;
	position.top = 40 + 10;
	position.right = 40 + 10 + 122 + 10 + 122 + 10 + 122;
	position.bottom = 40 + 10 + 726;

	ButtonsList* list = new ButtonsList;
	list->position.left = position.left;
	list->position.top = position.top;
	list->position.right = position.right;
	list->position.bottom = position.bottom;

	for (int unitType = 0; unitType < OBJECT_TYPE_UNIT; unitType++)
	{
		DirectionAnimationResource* res = (DirectionAnimationResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_OBJECTS)
			->get(OBJECT_TYPE_UNIT)
			->get(unitType)->get(ACTION_STAY);

		GuiImage image = { res->bufferID, *res->getFrame(DIRECTION_UP, 0) };

		list->addItem(unitType, image);
	}

	list->onItemChanged = ulOnItemChanged;

	add(list);
}