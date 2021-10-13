#include "MovableObject.h"
#include <math.h>
#include "../World.h"

extern World world;

MovableObject::MovableObject()
{
	direction = DIRECTION_UP;
}

MovableObject::~MovableObject()
{

}


void MovableObject::move(float target_x, float target_y)
{

	float distX = target_x - coordinates.x;
	float distY = target_y - coordinates.y;

	float distance = sqrt(distX * distX + distY * distY);

	float dx = distX / distance * speed;
	float dy = distY / distance * speed;

	if (fabs(dx) > fabs(distX)) coordinates.x = target_x;
	else coordinates.x += dx;

	if (fabs(dy) > fabs(distY)) coordinates.y = target_y;
	else coordinates.y += dy;

	updateDirection(dx, dy);
	udatePosition();
}


void MovableObject::updateDirection(float dx, float dy)
{
	if (dx > 0)
	{
		if (dy < 0) 
		{
			float tg = -dy / dx;

			float angle30 = 0.5774f;
			float angle60 = 1.732f;

			if (tg >= angle30)
			{
				if (tg >= angle60)
				{
					direction = DIRECTION_UP;
				}
				else
				{
					direction = DIRECTION_UP_RIGHT;
				}
			}
			else
			{
				direction = DIRECTION_RIGHT;
			}
		}

		if (dy == 0) direction = DIRECTION_RIGHT;
		
		if (dy > 0)
		{
			float tg = dy / dx;

			float angle30 = 0.5774f;
			float angle60 = 1.732f;

			if (tg >= angle30)
			{
				if (tg >= angle60)
				{
					direction = DIRECTION_DOWN;
				}
				else
				{
					direction = DIRECTION_DOWN_RIGHT;
				}
			}
			else
			{
				direction = DIRECTION_RIGHT;
			}
		}
	}

	if (dx < 0)
	{
		if (dy < 0)
		{
			float tg = dy / dx;

			float angle30 = 0.5774f;
			float angle60 = 1.732f;

			if (tg >= angle30)
			{
				if (tg >= angle60)
				{
					direction = DIRECTION_UP;
				}
				else
				{
					direction = DIRECTION_UP_LEFT;
				}
			}
			else
			{
				direction = DIRECTION_LEFT;
			}
		}
		if (dy == 0) direction = DIRECTION_LEFT;
		if (dy > 0)
		{
			float tg = -dy / dx;

			float angle30 = 0.5774f;
			float angle60 = 1.732f;

			if (tg >= angle30)
			{
				if (tg >= angle60)
				{
					direction = DIRECTION_DOWN;
				}
				else
				{
					direction = DIRECTION_DOWN_LEFT;
				}
			}
			else
			{
				direction = DIRECTION_LEFT;
			}
		}
	}

	if (dx == 0)
	{
		if (dy <= 0) direction = DIRECTION_UP;
		else direction = DIRECTION_DOWN;
	}
}

void MovableObject::udatePosition()
{
	WorldPosition p = { coordinates.x / POSITION_SIZE, coordinates.y / POSITION_SIZE };

	if (position.x != p.x || position.y != p.y) {
		world.map->cells[position.x][position.y].removeObject(this);
		position.x = p.x;
		position.y = p.y;
		world.map->cells[position.x][position.y].addObject(this);
	}
}