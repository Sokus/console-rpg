#pragma once
#include "Frame.h"
#include "Containers.h"

class BufferQueueElement
{
private:
	Frame frame;
	vector2i position = { 0,0 };
	int depth = INT_MIN;
public:
	BufferQueueElement();
	BufferQueueElement(Frame frame, vector2i position, int depth);

	Frame& GetFrame();
	vector2i GetPosition();
	int GetDepth();
};

