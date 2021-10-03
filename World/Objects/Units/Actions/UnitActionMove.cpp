#include "UnitActionMove.h"

UnitActionMove::UnitActionMove(Unit* unit) : Action(unit)
{
	type = ACTION_MOVE;
}

void UnitActionMove::execute()
{

}