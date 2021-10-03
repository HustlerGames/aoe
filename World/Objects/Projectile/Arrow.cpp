#include "Arrow.h"
#include "../../../World/World.h"


extern World world;

Arrow::Arrow(float from_x, float from_y, float to_x, float to_y)
{
	x = from_x;
	y = from_y;
	target_x = to_x;
	target_y = to_y;
	projectile_type = PROJECTILE_TYPE_ARROW;
}


void Arrow::update()
{
	/*if (hit) return;

	move(target_x, target_y);

	if (coordinates.x == target_x && coordinates.y == target_y)
	{

		Point point = positionByCoords(target_x, target_y);
		Object* p = world.map.getObject(point.x, point.x);
		if (p) {
			p->hit(this);
		}

		hit = true;
	}
	*/
}

