// This class is used to represent one animation frame, typically an array with color IDs

#pragma once
#include <vector>

#include "Containers.h"

class Frame
{
private:
	vector2i size;
	std::vector<std::vector<int>> frame_data;

public:
	Frame();
	Frame(int x, int y);
	int Read(int x, int y);
	void Write(int value, int x, int y);
	vector2i GetSize();
};

