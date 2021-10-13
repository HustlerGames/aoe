#include "Viewport.h"

extern Ñanvas canvas;

Viewport::Viewport()
{
	x = 3000;
	y = 500;
	width = 1920;
	height = 770;
	screen_x = 0;
	screen_y = 62;
	speed = 10;
}

void Viewport::move(float vx, float vy)
{
	x += vx * speed;
	y += vy * speed;

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if ((x + width) > canvas.width)
		x = canvas.width - width;
	if ((y + height) > canvas.height)
		y = canvas.height - height;
}

bool Viewport::has(Rect* rect)
{
	if (rect->left > width) return false;
	if (rect->top > height) return false;
	if (rect->right < 0) return false;
	if (rect->bottom < 0) return false;

	return true;
}

