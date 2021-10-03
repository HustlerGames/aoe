#include "Button.h"


void Button::onLMouse(int x, int y)
{
	active = true;
	onButtonClick(this);
}

void Button::render()
{
	

	if (active)
	{
		GS.drawRectangle(
			position.left,
			position.top,
			position.right,
			position.bottom,
			BRUSH_RED_TRANSPARENT
		);
	}
	
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