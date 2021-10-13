#include "Arrow.h"
#include "World/World.h"


extern World world;

Arrow::Arrow(float from_x, float from_y, float to_x, float to_y)
{
	projectile_type = PROJECTILE_TYPE_ARROW;
	damage = 5;
	x = from_x;
	y = from_y;
	h = 60;
	target_x = to_x;
	target_y = to_y;
	speed = 20;
}

void Arrow::update()
{
	move(target_x, target_y);

	if (coordinates.x == target_x && coordinates.y == target_y)
	{
		WorldCoordinates target = { target_x, target_y };
		WorldPosition pos = world.map->positionByCoords(target);
		Object* ptarget = world.map->cells[pos.x][pos.y].findObjectType(OBJECT_TYPE_UNIT);
		
		if (ptarget) ptarget->takeDamage(damage);
	}
}

