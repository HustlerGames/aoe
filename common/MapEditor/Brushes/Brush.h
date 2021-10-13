#pragma once


class Brush
{
public:
	int objectId;

	Brush();
	virtual ~Brush();
	virtual void edit(int x, int y);
	virtual void setObject(int i);
private:

};
