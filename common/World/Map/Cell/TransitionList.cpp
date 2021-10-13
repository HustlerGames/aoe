#include "TransitionList.h"
#include "../../Constants.h"


TransitionList::~TransitionList()
{
	clear();
}



void TransitionList::clear()
{
	TransitionItem* p = root;

	while (root) {
		p = root->next;
		delete root;
		root = p;
	}

	root = nullptr;

	length = 0;
}


void TransitionList::add(Transition* transition)
{
	// add
	TransitionItem* item = new TransitionItem;
	item->transition = transition;
	item->next = nullptr;

	if (root == nullptr)
	{
		root = item;
		length=1;
		return;
	} 
	


	// sort
	TransitionItem* p = root;
	TransitionItem* t = nullptr;
	TransitionItem* prev = nullptr;
	int dir = transition->direction;
	int p_dir;


	while (p)
	{
		p_dir = p->transition->direction;

		if (
			(dir == p_dir) ||
			(dir == DIRECTION_UP && (p_dir == DIRECTION_UP_LEFT || p_dir == DIRECTION_UP_RIGHT)) ||
			(dir == DIRECTION_RIGHT && (p_dir == DIRECTION_UP_RIGHT || p_dir == DIRECTION_DOWN_RIGHT)) ||
			(dir == DIRECTION_DOWN && (p_dir == DIRECTION_DOWN_RIGHT || p_dir == DIRECTION_DOWN_LEFT)) ||
			(dir == DIRECTION_LEFT && (p_dir == DIRECTION_UP_LEFT || p_dir == DIRECTION_DOWN_LEFT))
			)
		{
			t = p;
			p = p->next;

			if (prev == nullptr)
			{
				root = p;
			}
			else 
			{
				prev->next = p;
			}

			delete t->transition;
			delete t;
			t = nullptr;

		}
		else 
		{
			prev = p;
			p = p->next;
		}
	}

	// add
	if (root) {
		p = root;
		while (p->next)
		{
			p = p->next;
		}

		p->next = item;
	}
	else {
		root = item;
	}

	length = 0;
	p = root;
	while (p)
	{
		length++;
		p = p->next;
	}

	
}


void TransitionList::reset()
{
	current = root;
}
void TransitionList::next()
{
	if(current) current = current->next;
}

Transition* TransitionList::getCurrent()
{
	if (current) return current->transition;
	return nullptr;
}

int TransitionList::getLength()
{
	return length;
}

