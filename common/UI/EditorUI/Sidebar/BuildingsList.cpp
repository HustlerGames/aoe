#include "BuildingsList.h"
#include "UI/Controls/ButtonsList.h"
#include "MapEditor/MapEditor.h"

extern Resources resources;
extern MapEditor editor;

void blOnItemChanged(int i)
{
	editor.setBrush(BUILDING_BRUSH);
	editor.setBrushObject(i);
}

BuildingsList::BuildingsList()
{

	position.left = 40 + 10 + 122 + 10 + 122 + 10 + 122 + 10;
	position.top = 40 + 10;
	position.right = 40 + 10 + 122 + 10 + 122 + 10 + 122 + 10 + 122;
	position.bottom = 40 + 10 + 726;

	ButtonsList* list = new ButtonsList;
	list->position.left = position.left;
	list->position.top = position.top;
	list->position.right = position.right;
	list->position.bottom = position.bottom;

	for (int i = 0; i < BUILDING_TYPES_COUNT; i++)
	{
		StateSpriteResource* res = (StateSpriteResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_OBJECTS)
			->get(OBJECT_TYPE_BUILDING)
			->get(i);

		if (res == nullptr) 
			continue;

		GuiImage image = { res->bufferID, res->states[BUILDING_STATE_READY] };

		list->addItem(i, image);
	}

	list->onItemChanged = blOnItemChanged;

	add(list);
}