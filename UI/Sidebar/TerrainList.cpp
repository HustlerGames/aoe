#include "TerrainList.h"
#include "../Controls/ButtonsList.h"
#include "../../Editor/Editor.h"

extern Resources resources;
extern Editor editor;

void tlOnItemChanged(int i)
{
	editor.setBrush(TERRAIN_BRUSH);
	editor.setBrushObject(i);
}

TerrainList::TerrainList()
{
	position.left = 40 + 10;
	position.top = 40 + 10;
	position.right = 40 + 10 + 122;
	position.bottom = 40 + 10 + 726;

	ButtonsList* list = new ButtonsList;
	list->position.left = position.left;
	list->position.top = position.top;
	list->position.right = position.right;
	list->position.bottom = position.bottom;

	for (int i = 0; i < GROUND_TYPE_COUNT; i++)
	{
		TerrainResource* res = (TerrainResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_TERRAIN)
			->get(i);

		GuiImage image = { res->bufferID, res->tile[0] };

		list->addItem(i, image);
	}

	list->onItemChanged = tlOnItemChanged;

	add(list);
}