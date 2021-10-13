#include "GameUI.h"

void GameUI::init()
{
	panel = new Panel;
	menu = new Menu;
	header = new Header;

	add(panel);
	add(menu);
	add(header);
}