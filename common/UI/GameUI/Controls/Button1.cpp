#include "Button1.h"

Button1::Button1()
{
	
}

void Button1::render()
{
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

void Button1::onLMouse(int x, int y)
{
	onButtonClick(this);
}