#pragma once
#include "World/Objects/MovableObject.h"


class Projectile :
    public MovableObject
{
public:
    int projectile_type;
    float x;
    float y;
    float h;
    float target_x;
    float target_y;
    float target_h;
    float damage = 0;
    bool hit = false;
    Projectile();
    void update();
};

