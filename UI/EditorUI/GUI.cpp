#include "GUI.h"

extern GraphicSystem GS;

void GUI::render()
{

	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->visible)
			wndList[i]->render();
	}
}

bool GUI::onLMouse(int x, int y)
{
	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->visible)
			if (wndList[i]->isInner(x, y))
			{
				wndList[i]->onLMouse(x, y);
				return true;
			}

	}

	return false;
}


bool GUI::isInsideWnd(int x, int y)
{

	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->visible)
			if (wndList[i]->isInner(x, y))
			{
				return true;
			}

	}

	return false;
}


bool GUI::onRMouse(int x, int y)
{
	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->visible)
			if (wndList[i]->isInner(x, y))
			{
				wndList[i]->onRMouse(x, y);
				return true;
			}

	}

	return false;
}


void GUI::add(Wnd* child)
{
	std::shared_ptr<Wnd> spchild(child);
	wndList.push_back(spchild);
}