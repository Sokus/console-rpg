// This class hold a frame that has to be rendered, it says where should it be on the screen (position after calculating all the offsets Entities could have etc).
// It also has a depth value, which helps determine which objects should render in front of which.

#pragma once
#include "Animator/Frame.h"
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

