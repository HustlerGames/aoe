#include "Commands.h"




Commands::Commands()
{
	// 512x144
	position.left = 682;
	position.right = position.left + 512;
	position.top = 850;
	position.bottom = position.top + 144;

	SpriteResource* spRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_COMMANDS);

	image.frame = spRes->frame;
	image.bufferID = spRes->bufferID;
}

void Commands::render()
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

	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->visible)
			wndList[i]->render();
	}
}