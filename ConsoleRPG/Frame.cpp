#include "Frame.h"
Frame::Frame()
{
};

Frame::Frame(int x, int y)
{
	frame_data.clear();
	std::vector<int> temporary;
	for (int iy = 0; iy < y; iy++)
	{
		temporary.emplace_back(15);
	}
	for (int ix = 0; ix < x; ix++)
	{
		frame_data.emplace_back(temporary);
	}
	size.x = x;
	size.y = y;
};

int Frame::Read(int x, int y)
{
	return frame_data[x][y];
};

void Frame::Write(int value, int x, int y)
{
	frame_data[x][y] = value;
};

vector2i Frame::GetSize()
{
	return size;
};