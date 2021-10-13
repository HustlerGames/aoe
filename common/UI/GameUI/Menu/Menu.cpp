#include "Menu.h"


void MenuButtonCloseClick(Button1* pButton)
{
	pButton->parent->visible = false;
}

void MenuButtonSaveClick(Button1* pButton)
{

}

void MenuButtonLoadClick(Button1* pButton)
{

}

void MenuButtonQuitClick(Button1* pButton)
{

}

void MenuButtonSettingsClick(Button1* pButton)
{

}

Menu::Menu()
{
	position.left = 717;
	position.top = 236;
	position.right = 717 + 490;
	position.bottom = 236 + 500;

	SpriteResource* spRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_MENU);
	
	image.bufferID = spRes->bufferID;
	image.frame = spRes->frame;

	int buttonWidth = 416;
	int buttonHeight = 76;

	int buttons_left_pos = position.left + 40;
	//----
	int buttonTop = position.top + 50;

	SpriteResource* btnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_MENU_BUTTON_CLOSE);

	Button1* btnClose = new Button1;
	btnClose->position = { buttons_left_pos , buttons_left_pos + buttonWidth,  buttonTop, buttonTop + buttonHeight };
	btnClose->image.frame = btnRes->frame;
	btnClose->image.bufferID = btnRes->bufferID;
	btnClose->onButtonClick = MenuButtonCloseClick;
	add(btnClose);
	//--

	//----
	buttonTop = position.top + 50 + buttonHeight + 0;

	btnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_MENU_BUTTON_LOAD);

	Button1* btnLoad = new Button1;
	btnLoad->position = { buttons_left_pos , buttons_left_pos + buttonWidth,  buttonTop, buttonTop + buttonHeight };
	btnLoad->image.frame = btnRes->frame;
	btnLoad->image.bufferID = btnRes->bufferID;
	btnLoad->onButtonClick = MenuButtonLoadClick;
	add(btnLoad);
	//--
	
	//----
	buttonTop = position.top + 50 + (buttonHeight + 0)*2;

	btnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_MENU_BUTTON_SAVE);

	Button1* btnSave = new Button1;
	btnSave->position = { buttons_left_pos , buttons_left_pos + buttonWidth,  buttonTop, buttonTop + buttonHeight };
	btnSave->image.frame = btnRes->frame;
	btnSave->image.bufferID = btnRes->bufferID;
	btnSave->onButtonClick = MenuButtonSaveClick;
	add(btnSave);
	//--
	//----
	buttonTop = position.top + 50 + (buttonHeight + 0) * 3;

	btnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_MENU_BUTTON_SETTINGS);

	Button1* btnSettings = new Button1;
	btnSettings->position = { buttons_left_pos , buttons_left_pos + buttonWidth,  buttonTop, buttonTop + buttonHeight };
	btnSettings->image.frame = btnRes->frame;
	btnSettings->image.bufferID = btnRes->bufferID;
	btnSettings->onButtonClick = MenuButtonSettingsClick;
	add(btnSettings);
	//--

	//----
	buttonTop = position.top + 50 + (buttonHeight + 0) * 4;

	btnRes = (SpriteResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_MENU_BUTTON_QUIT);

	Button1* btnQuit = new Button1;
	btnQuit->position = { buttons_left_pos , buttons_left_pos + buttonWidth,  buttonTop, buttonTop + buttonHeight };
	btnQuit->image.frame = btnRes->frame;
	btnQuit->image.bufferID = btnRes->bufferID;
	btnQuit->onButtonClick = MenuButtonQuitClick;
	add(btnQuit);
	//--

}


void Menu::render()
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

