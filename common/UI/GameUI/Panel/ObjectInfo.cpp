#include "ObjectInfo.h"
#include "World/Objects/Units/Unit.h"

ObjectInfo::ObjectInfo()
{
	position.left = 450;
	position.top = 815 + 33;
	position.right = 671;
	position.bottom = 1077;

	SpriteResource* spRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_PREVIEW);

	image.frame = spRes->frame;
	image.bufferID = spRes->bufferID;
}

void ObjectInfo::setObject(Object* object)
{
	currentObject = object;
}

void ObjectInfo::render()
{
	// background
	GS.draw(
		image.bufferID,
		image.frame.x,
		image.frame.y,
		image.frame.width,
		image.frame.height,
		position.left,
		position.top,
		image.frame.width,
		image.frame.height
	);

	if (currentObject)
	{
		int type = currentObject->getType();

		if (type == OBJECT_TYPE_UNIT)
		{
			Unit* unit = (Unit*)currentObject;
			DirectionAnimationResource* unitRes = (DirectionAnimationResource*)resources.pRoot
				->get(RESOURCE_CATEGORY_OBJECTS)->get(OBJECT_TYPE_UNIT)->get(unit->unit_type)->get(ACTION_STAY);

			GuiImage img;
			img.frame = *unitRes->getFrame(DIRECTION_DOWN, 0);
			img.bufferID = unitRes->bufferID;

			GS.draw(
				img.bufferID,
				img.frame.x,
				img.frame.y,
				img.frame.width,
				img.frame.height,
				position.left + 20,
				position.top + 20,
				img.frame.width,
				img.frame.height
			);

		}

		if (type == OBJECT_TYPE_BUILDING)
		{

		}

		if (type == OBJECT_TYPE_RESOURCE)
		{

		}
	}
}

