#pragma once

#include "UI/GUI.h"
#include "Sidebar/Sidebar.h"

class EditorUI : public GUI 
{
public:
	Sidebar* sidebar;
	void init();
};

