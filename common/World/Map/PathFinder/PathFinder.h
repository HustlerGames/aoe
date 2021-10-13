#pragma once

#define DEFAULT_DISTANCE  99999

struct PFCoord {
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int distance = 0;
};

struct PFPosition {
	unsigned int x = 0;
	unsigned int y = 0;
	bool pass = true;
	unsigned int distance = DEFAULT_DISTANCE;

	PFPosition* up = nullptr;
	PFPosition* up_right = nullptr;
	PFPosition* right = nullptr;
	PFPosition* down_right = nullptr;
	PFPosition* down = nullptr;
	PFPosition* down_left = nullptr;
	PFPosition* left = nullptr;
	PFPosition* up_left = nullptr;

	PFPosition* next = nullptr;
};


class PFPath {
public:
	PFPath();
	int getLength();
	PFCoord getCurrent();
	bool addPosition(PFPosition* position);
	PFCoord* next();
	void reset();
	bool isPath(int x, int y, int dest_x, int dest_y);
	void save();
	void restore();
	void clear();
	PFCoord getEnd();
	int getLastLength();
private:
	int length = 0;
	int current_position = 0;
	PFCoord positions[500] = {};
	int saved_curpos = 0;
	int saved_length = 0;
};


class Wave {
public:
	
	Wave();
	~Wave();
	void push(PFPosition* position);
	PFPosition* shift();
	int getLength();

private:
	PFPosition* pointer = nullptr;
	PFPosition* end = nullptr;
	int length = 0;


};



class PathFinder {
public:
	PathFinder(int w, int h);
	~PathFinder();
	bool isPass(int x, int y);
	void clear();
	PFPath* find(int x_from, int y_from, int x_dest, int y_dest, int width = 1, int height = 1);
	void setPass(int x, int y, bool pass);
	inline void mark(PFPosition* position, int distance);
	int getWidth();
	int getHeight();
	int getDistance(int x, int y);
	void setPassRect(int left, int top, int right, int bottom, bool pass);
private:

	int width = 0;
	int height = 0;
	Wave* pWave = nullptr;
	PFPosition** positions = nullptr;
	PFPosition* pointerTo(int x, int y);
	PFPath* readPath(PFPosition* position);
	inline PFPosition* compareDistance(PFPosition* min, PFPosition* pos);
};