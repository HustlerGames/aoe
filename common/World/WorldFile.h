#pragma once


class WorldFile
{
public:
	static bool save();
	static bool read();
private:
	static BOOL writeFloat(float i, HANDLE f);
	static BOOL writeInt(int i, HANDLE f);
	static float readFloat(HANDLE f);
	static int readInt(HANDLE f);
};