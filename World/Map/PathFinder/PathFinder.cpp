#include "PathFinder.h"




/*
* ”казываетс€ размер пол€
*/
PathFinder::PathFinder(int w, int h) {

	width = w;
	height = h;

	pWave = nullptr;

	// если это перенести в след. цикл, указатели будут строитьс€ на несуществующие элементы
	positions = new PFPosition*[width];
	for (int x = 0; x < width; x++)
	{
		positions[x] = new PFPosition[height];
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			positions[x][y].x = x;
			positions[x][y].y = y;
			positions[x][y].pass = true;
			positions[x][y].up = pointerTo(x, y - 1);
			positions[x][y].up_right = pointerTo(x + 1, y - 1);
			positions[x][y].right = pointerTo(x + 1, y);
			positions[x][y].down_right = pointerTo(x + 1, y + 1);
			positions[x][y].down = pointerTo(x, y + 1);
			positions[x][y].down_left = pointerTo(x - 1, y + 1);
			positions[x][y].left = pointerTo(x - 1, y);
			positions[x][y].up_left = pointerTo(x - 1, y - 1);
		}
	}
}


PathFinder::~PathFinder()
{
	int a = 0;
	for (int x = 0; x < width; x++)
	{
		delete[] positions[x];
	}

	delete[] positions;
}


PFPosition* PathFinder::pointerTo(int x, int y) {

	if (x >= 0 && x < width && y >= 0 && y < height) {
		return &positions[x][y];
	}
	
	return nullptr;
}

/*
* ≈сть ли проход в указанной позиции
*/
bool PathFinder::isPass(int x, int y)
{
	return positions[x][y].pass;
}

/*
* »щет путь от позиции до позиции
*/
PFPath* PathFinder::find(int x_from, int y_from, int x_dest, int y_dest, int width_dest, int height_dest) {
	
	clear();

	int right = x_dest + width_dest;
	int bottom = y_dest + height_dest;


	PFPosition* position = &positions[x_from][y_from];
	position->distance = 0;

	pWave = new Wave;
	pWave->push(position);
	
	int distance;
	bool found = false;
	while (pWave->getLength()) {

		position = pWave->shift();

		if ( position->x >= x_dest &&
			 position->y >= y_dest &&
			 position->x < right && 
			 position->y < bottom  )
		{
			found = true;
			break;
		}

		distance = position->distance + 1;

		mark(position->up,		   distance);
		mark(position->up_right,   distance);
		mark(position->right,      distance);
		mark(position->down_right, distance);
		mark(position->down,	   distance);
		mark(position->down_left,  distance);
		mark(position->left,       distance);
		mark(position->up_left,    distance);
	}

	delete pWave;

	if (found)
	{
		return readPath(position);
	}

	return nullptr;
}



int PathFinder::getDistance(int x, int y) {
	return positions[x][y].distance;
}

PFPosition* PathFinder::compareDistance(PFPosition* walker, PFPosition* pos)
{
	if (pos && pos->distance < walker->distance)
		return pos;

	return walker;
}

 PFPath* PathFinder::readPath(PFPosition *position)
{
	PFPath *pPath = new PFPath;

	pPath->addPosition(position);

	PFPosition* walker = position;
	PFPosition* min;

	while (walker->distance) {
		
		min = walker;
		
		min = compareDistance(min, walker->up);
		min = compareDistance(min, walker->right);
		min = compareDistance(min, walker->down);
		min = compareDistance(min, walker->left);
		min = compareDistance(min, walker->up_right);
		min = compareDistance(min, walker->down_right);
		min = compareDistance(min, walker->down_left);
		min = compareDistance(min, walker->up_left);

		walker = min;

		pPath->addPosition(walker);
	}
	
	return pPath;
}

void PathFinder::clear()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			positions[x][y].distance = DEFAULT_DISTANCE;
			positions[x][y].next = nullptr;
		}
	}
	
}



void PathFinder::mark(PFPosition* position, int distance)
{
	if (position && position->pass && position->distance > distance) {
		position->distance = distance;
		pWave->push(position);
	}
}


void PathFinder::setPass(int x, int y, bool pass)
{
	positions[x][y].pass = pass;
}

void PathFinder::setPassRect(int left, int top, int right, int bottom, bool pass)
{
	for (int x = left; x < right; x++) {
		for (int y = top; y < bottom; y++) {
			setPass(x, y, pass);
		}
	}
}

int PathFinder::getWidth()
{
	return width;
}


int PathFinder::getHeight()
{
	return height;
}



