#pragma once

#include "../Structures.h"
#include "AnimationResource.h"


class DirectionAnimationResource :
	public AnimationResource
{
public:
	int cols;
	int rows;

	DirectionAnimationResource(int _cols, int _rows);
	~DirectionAnimationResource();

	void setFrame(int row, int col, int x, int y, int w, int h, int offset_x, int offset_y);
	Frame* getFrame(int dir, int frame);
private:
	Frame** frames;
};
