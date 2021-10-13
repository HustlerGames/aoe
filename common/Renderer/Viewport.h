#pragma once

#include "Structures.h"

class Viewport
{

public:
	int x;
	int y;
	int width;
	int height;
	int screen_x;
	int screen_y;
	float speed;

	Viewport();

	void move(float x, float y);
	bool has(Rect* rect);
};