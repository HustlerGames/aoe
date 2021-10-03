#include "SimpleObjectsList.h"
#include "../../World/Constants.h"
#include "../Controls/ButtonsList.h"
#include "../../Editor/Editor.h"

extern Resources resources;
extern Editor editor;

void solOnItemChanged(int i)
{
	editor.setBrush(OBJECT_BRUSH);
	editor.setBrushObject(i);
}


SimpleObjectsList::SimpleObjectsList()
{
	position.left = 40 + 10 + 122 + 10;
	position.top = 40 + 10;
	position.right = 40 + 10 + 122 + 10 + 122;
	position.bottom = 40 + 10 + 726;

	ButtonsList* list = new ButtonsList;
	list->position.left = position.left;
	list->position.top = position.top;
	list->position.right = position.right;
	list->position.bottom = position.bottom;
	
	for (int i = 0; i < SIMPLE_OBJECTS_COUNT; i++)
	{
		SpriteResource* res = (SpriteResource*)resources.pRoot
			->get(RESOURCE_CATEGORY_OBJECTS)
			->get(OBJECT_TYPE_SIMPLE)
			->get(i);

		GuiImage image = { res->bufferID, res->frame };

		list->addItem(i, image);
	}
	
	list->onItemChanged = solOnItemChanged;

	add(list);
}