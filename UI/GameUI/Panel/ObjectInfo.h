#pragma once

#include "../../Wnd.h"
#include "../../../World/Objects/Object.h"

class ObjectInfo : public Wnd
{
public:
	GuiImage image;
	Object* currentObject = nullptr;
	ObjectInfo();
	void setObject(Object* object);
	void render();
};