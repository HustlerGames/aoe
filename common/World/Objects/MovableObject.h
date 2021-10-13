#pragma once

#include "Object.h"

class MovableObject : public Object
{
public:
	int speed;
	int direction;

	MovableObject();
	~MovableObject();
	void move(float target_x, float target_y);
	void updateDirection(float dx, float dy);
private:
	void udatePosition();
};

