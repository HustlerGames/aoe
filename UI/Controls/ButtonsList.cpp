#include "ButtonsList.h"
#include "Button.h"
#include "../../Editor/Editor.h"

extern Resources resources;
extern Editor editor;

void btnToggleClick(ToggleButton* button);
void btnDownClick(Button* button);
void btnUpClick(Button* button);

void ButtonsList::render()
{
	updateButtonPositions();
	Wnd::render();
}

ButtonsList::ButtonsList()
{
	position = {0,0,0,0};

	GUIResource* spRes = (GUIResource*)resources.pRoot
		->get(RESOURCE_CATEGORY_GUI)->get(RESOURCE_GUI_ONE);

	up = new Button;
	up->onButtonClick = btnUpClick;
	up->image.frame = spRes->frames[GUI_BUTTONSLIST_SCROLL_UP];
	up->image.bufferID = spRes->bufferID;

	down = new Button;
	down->onButtonClick = btnDownClick;
	down->image.frame = spRes->frames[GUI_BUTTONSLIST_SCROLL_DOWN];
	down->image.bufferID = spRes->bufferID;

	add(up);
	add(down);
}





void ButtonsList::addToButtonsList(ToggleButton* child)
{
	std::shared_ptr<ToggleButton> spchild(child);
	btnsList.push_back(spchild);
}


void ButtonsList::addItem(int value, GuiImage image)
{
	ToggleButton* button = new ToggleButton;
	button->value = value;
	button->image = image;
	button->onButtonActive = btnToggleClick;
	add(button);
	addToButtonsList(button);
}


void ButtonsList::updateButtonPositions()
{
	int height = position.bottom - position.top;
	int clientAreaH = height - 2 * SCROLL_BUTTONS_H;
	pageSize = clientAreaH / (BUTTON_SIZE_Y + 2 * BUTTONS_BORDER);
	pages = (int)(GROUND_TYPE_COUNT / pageSize);

	if ((GROUND_TYPE_COUNT % pageSize) > 0)
		pages++;

	up->position.left = position.left + 10;
	up->position.top = position.top + 10;
	up->position.right = position.right - 10;
	up->position.bottom = position.top + 10 + SCROLL_BUTTONS_H;

	down->position.left = position.left + 10;
	down->position.top = position.top + 10 + SCROLL_BUTTONS_H + clientAreaH;
	down->position.right = position.right - 10;
	down->position.bottom = down->position.top + SCROLL_BUTTONS_H;



	for (int i = 0; i < btnsList.size(); i++)
	{
		btnsList[i]->visible = false;
	}

	int startItem = pageNum * pageSize;
	int endItem = startItem + pageSize;
	if (endItem > btnsList.size())
		endItem = btnsList.size();

	int itemsCount = endItem - startItem;

	for (int i = 0; i < itemsCount; i++ )
	{
		btnsList[i + startItem]->visible = true;
		Position* p = &btnsList[i + startItem]->position;
		p->left = position.left + LIST_X_PADDING;
		p->top = 10 + position.top + i*(BUTTON_SIZE_Y + 2 * BUTTONS_BORDER) + SCROLL_BUTTONS_H;
		p->right = p->left + BUTTON_SIZE_X;
		p->bottom = p->top + BUTTON_SIZE_Y;
	}


}

void ButtonsList::pageUp()
{
	if (pageNum > 0) pageNum--;
	updateButtonPositions();
}


void ButtonsList::pageDown()
{
	if (pageNum < (pages - 1)) pageNum++;
	updateButtonPositions();
}


void btnUpClick(Button* button)
{
	((ButtonsList*)button->parent)->pageUp();
}


void btnDownClick(Button* button)
{
	((ButtonsList*)button->parent)->pageDown();
}


void btnToggleClick(ToggleButton* button)
{
	int terrainResourceId = button->value;

	ButtonsList* list = (ButtonsList*)button->parent;

	for (int i = 0; i < list->btnsList.size(); i++)
	{
		list->btnsList[i]->active = false;
	}

	button->active = true;

	ButtonsList* p = (ButtonsList*)button->parent;
	if(p->onItemChanged) p->onItemChanged(button->value);
}
