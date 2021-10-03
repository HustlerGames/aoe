#include "Wnd.h"
#include "../GraphicSystem/GraphicSystem.h"



Wnd::Wnd()
{

}

Wnd::~Wnd()
{

}

void Wnd::render()
{
	if (visible == false) return;

	GS.fillRectangle(position.left, position.top, position.right, position.bottom, color);

	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->visible)
			wndList[i]->render();
	}

}


bool  Wnd::isInner(int x, int y)
{
	return (x > position.left && y > position.top && x < position.right&& y < position.bottom);
}

void Wnd::onLMouse(int x, int y)
{
	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->isInner(x, y))
		{
			if(wndList[i]->visible)
				wndList[i]->onLMouse(x, y);
		}

	}
}

void Wnd::onRMouse(int x, int y)
{
	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->isInner(x, y))
		{
			if (wndList[i]->visible)
				wndList[i]->onRMouse(x, y);
		}

	}
}


void Wnd::add(Wnd* child)
{
	child->parent = this;
	std::shared_ptr<Wnd> spchild(child);
	wndList.push_back(spchild);
}