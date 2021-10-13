#include "Object.h"
#include <math.h>

Object::Object()
{
	width = 1;
	height = 1;
	type = 0;
}

Object::~Object()
{

}

int Object::getType()
{
	return type;
}

void Object::update(){}

float Object::distanceTo(Object* pTarget)
{
	int dx = position.x - pTarget->position.x;
	int dy = position.y - pTarget->position.y;

	float R = sqrt(dx * dx + dy * dy);

	return floor(R);
}

void Object::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Object::takeDamage(float damage)
{

}