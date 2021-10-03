#pragma once
#include "../Object.h"

#define PROJECTILE_TYPE_ARROW 0


class Projectile :
    public Object
{
public:
    int projectile_type;
    float x;
    float y;
    float h;
    float target_x;
    float target_y;
    float target_h;
    bool hit = false;
    Projectile();
    void update();
};

