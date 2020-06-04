#include "BufferQueueElement.h"

BufferQueueElement::BufferQueueElement()
{
	this->frame = *(new Frame(5, 5));
};

BufferQueueElement::BufferQueueElement(Frame frame, vector2i position, int depth)
{
	this->frame = *(new Frame(frame));
	this->position = position;
	this->depth = depth;
};

Frame& BufferQueueElement::GetFrame()
{
	return frame;
};

vector2i BufferQueueElement::GetPosition()
{
	return position;
};

int BufferQueueElement::GetDepth()
{
	return depth;
};
