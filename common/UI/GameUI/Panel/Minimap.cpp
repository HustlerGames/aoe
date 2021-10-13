#include "Minimap.h"

Minimap::Minimap()
{
	// w = 378
	// h = 231

	position.left = 40;
	position.top = 30 + 815;
	position.right = position.left + 378;
	position.bottom = position.top + 231;

	SpriteResource* spRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_MINIMAP);

	image.frame = spRes->frame;
	image.bufferID = spRes->bufferID;
}

void Minimap::render()
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
}

