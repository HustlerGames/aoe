#pragma once

struct Tile {
	int resource_id;
	int tile_id;
};

struct Transition {
	int direction;
	Tile tile;
};


struct TransitionItem {
	Transition* transition = nullptr;
	TransitionItem* next = nullptr;
};


class TransitionList {
public:
	~TransitionList();
	void add(Transition* transition);
	void clear();
	void reset();
	void next();
	Transition* getCurrent();
private:
	TransitionItem* current = nullptr;
	TransitionItem* root = nullptr;
};
