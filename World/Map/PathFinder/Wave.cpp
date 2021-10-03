#include "PathFinder.h"

Wave::Wave()
{
	length = 0;
	pointer = 0;
	end = 0;
}

void Wave::push(PFPosition* position)
{
	position->next = 0;
	if (end) end->next = position;
	end = position;
	if (!pointer) pointer = position;
	length++;
}


PFPosition* Wave::shift() {

	PFPosition* p = pointer;

	if (pointer) {
		pointer = pointer->next;
		length--;
	}
	else {
		end = 0;
	}

	return p;
}

int Wave::getLength()
{
	return length;
}

Wave::~Wave()
{
	
}