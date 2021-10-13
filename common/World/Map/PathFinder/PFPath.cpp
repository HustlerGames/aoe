#pragma once

#include "PathFinder.h"

PFPath::PFPath() {
	current_position = 0;
	length = 0;
}

PFCoord PFPath::getCurrent() {
	return positions[current_position];
}

bool PFPath::addPosition(PFPosition* position) {
	if (length < 499) {
		positions[length].x = position->x;
		positions[length].y = position->y;
		positions[length].distance = position->distance;
		length++;
		current_position = length - 1;

		return true;
	}

	return false;
}


PFCoord* PFPath::next() {
	
	if (current_position) {
		return &positions[--current_position];
	}
	
	return nullptr;
}


void PFPath::reset() {
	current_position = length - 1;
}


int PFPath::getLength()
{
	return length;
}

int PFPath::getLastLength()
{
	return current_position;
}


bool PFPath::isPath(int x, int y, int dest_x, int dest_y)
{
	return (positions[current_position].x == x && 
		    positions[current_position].y == y && 
			positions[0].x == dest_x && 
			positions[0].y == dest_y     );
}



void PFPath::save()
{
	saved_curpos = current_position;
}


void PFPath::restore()
{
	current_position = saved_curpos;
}


void PFPath::clear()
{
	current_position = 0;
	length = 0;
}


PFCoord PFPath::getEnd()
{
	return positions[0];
}