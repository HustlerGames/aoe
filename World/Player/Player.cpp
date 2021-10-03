#include "Player.h"

Player::Player()
{
	UnitCost[UNIT_PEASANT] = { 50,0,0 };
	UnitCost[UNIT_SWORDSMAN] = { 150,0,50 };
	UnitCost[UNIT_ARCHER] = { 100,50,0 };
}

void Player::update()
{
	
}

