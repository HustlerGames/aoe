#pragma once


#include "Projectile.h"


class Arrow : public Projectile
{
public:
    Arrow(float from_x, float from_y, float to_x, float to_y);
    void update();
};

