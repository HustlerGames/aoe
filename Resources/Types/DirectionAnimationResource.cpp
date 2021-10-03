#include "DirectionAnimationResource.h"


DirectionAnimationResource::~DirectionAnimationResource()
{
	for (int i = 0; i < cols; i++)
	{
		delete[] frames[i];
	}

	delete[] frames;
}




DirectionAnimationResource::DirectionAnimationResource(int _rows, int _cols)
{
	frames_count = _cols;
	cols = _cols;
	rows = _rows;

	frames = new Frame * [cols];

	for (int i = 0; i < cols; i++)
	{
		frames[i] = new Frame[rows];
	}


}


Frame* DirectionAnimationResource::getFrame(int dir, int frame)
{
	return &frames[frame][dir];
}




void DirectionAnimationResource::setFrame(int row, int col, int x, int y, int w, int h, int offset_x, int offset_y) {
	frames[col][row].x = x;
	frames[col][row].y = y;
	frames[col][row].width = w;
	frames[col][row].height = h;
	frames[col][row].offset_x = offset_x;
	frames[col][row].offset_y = offset_y;
}
