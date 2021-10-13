#include "ToggleButton.h"


void ToggleButton::onLMouse(int x, int y)
{
	active = true;
	onButtonActive(this);
}

void ToggleButton::render()
{
	if (active)
	{
		GS.drawRectangle(
			position.left,
			position.top,
			position.right,
			position.bottom,
			BRUSH_YELLOW_TRANSPARENT
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
		position.right - position.left,
		position.bottom - position.top
	);
}