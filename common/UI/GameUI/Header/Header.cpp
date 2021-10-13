#include "Header.h"
#include "UI/GameUI/Menu/Menu.h"
#include "UI/GameUI/GameUI.h"

extern GameUI gui;

void OpenMenuButtonClick(Button1* btn)
{
	gui.menu->visible = true;
}

Header::Header()
{
	position.left = 0;
	position.top = 0;
	position.right = 1920;
	position.bottom = 99;

	GUIResource* spRes = (GUIResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_HEADER);

	image.frame = spRes->frames[0];
	image.bufferID = spRes->bufferID;

	
	SpriteResource*  btnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_OPEN_MENU_BUTTON);

	Button1* menuButton = new Button1;
	menuButton->position = { 1680 , 1680 + 250, -3 , 90};
	menuButton->image.frame = btnRes->frame;
	menuButton->image.bufferID = btnRes->bufferID;
	menuButton->onButtonClick = OpenMenuButtonClick;
	add(menuButton);
}

void Header::render()
{
	// background
	GS.draw(
		image.bufferID,
		image.frame.x,
		image.frame.y,
		image.frame.width,
		image.frame.height,
		position.left,
		position.top,
		image.frame.width,
		image.frame.height
	);

	for (int i = 0; i < wndList.size(); i++)
	{
		if (wndList[i]->visible)
			wndList[i]->render();
	}
}

