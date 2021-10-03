#pragma once

#include "Unit.h"

class Archer : public Unit
{
public:
	Archer();
	void shoot(Object* pTarget);
};