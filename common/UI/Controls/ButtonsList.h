#pragma once

#include "../Wnd.h"
#include "ToggleButton.h"
#include <vector>
#include <memory>
#include "Button.h"

#define BUTTON_SIZE_X 102
#define BUTTON_SIZE_Y 52
#define BUTTONS_BORDER 10
#define SCROLL_BUTTONS_H 30
#define LIST_X_PADDING 10


class ButtonsList : public Wnd
{
public:
	std::vector<std::shared_ptr<ToggleButton>> btnsList;
	int pageNum = 0;
	int pages = 0;
	int pageSize = 0;
	Button* up = nullptr;
	Button* down = nullptr;

	ButtonsList();
	void addItem(int value, GuiImage image);
	void pageUp();
	void pageDown();
	void updateButtonPositions();
	void addToButtonsList(ToggleButton* child);
	void render();

	void (*onItemChanged)(int) = nullptr;
};