#include "Animation.h"


Animation::Animation(std::string file_location)
{
	std::ifstream file;
	file.open(file_location);
	if (!file)
	{
		std::cout << "Unable to open " << file_location << std::endl;
	}
	else
	{
		file >> name >> size.x >> size.y >> offset.x >> offset.y >> number_of_frames >> frames_per_second;
		//std::cout << name << " " << size.x << " " << size.y << " " << offset.x << " " << offset.y << " " << number_of_frames << " " << frames_per_second << "\n";
		Frame frame(size.x, size.y);
		int temporary_value;
		for (int f = 0; f < number_of_frames; f++)
		{
			for (int y = 0; y < size.y; y++)
			{
				for (int x = 0; x < size.x; x++)
				{
					file >> temporary_value;
					frame.Write(temporary_value, x, y);
					//std::cout << temporary_value << " ";
				}
				//std::cout << "\n";
			}
			//std::cout << "\n";
			frames.emplace_back(frame);
		}
	}
	file.close();
	Reset();
};

void Animation::Reset()
{
	current_frame = 0;
	start_time = clock();
	next_frame_time = clock() + (clock_t)(CLOCKS_PER_SEC / frames_per_second);
	end_time = start_time + (clock_t)(number_of_frames * (CLOCKS_PER_SEC / frames_per_second));
};

void Animation::Update()
{
	if (clock() >= next_frame_time && clock()<=end_time)
	{
		next_frame_time = clock() + (clock_t)(CLOCKS_PER_SEC / frames_per_second);

		if (current_frame < (number_of_frames - 1)) current_frame++;
	}
};

void Animation::SetLoop(bool value)
{
	loop = value;
} 

bool Animation::GetLoop()
{
	return loop;
}


vector2i Animation::GetAnimOffset()
{
	return offset;
};

Frame Animation::GetCurrentFrameObject()
{
	return frames[current_frame];
};

int Animation::GetCurrentFrameNumber()
{
	return current_frame;
};

void Animation::SetCurrentFrameNumber(int frame_number)
{
	current_frame = frame_number;
};


clock_t Animation::GetStartTime()
{
	return start_time;
};

void Animation::SetStartTime(clock_t start_time)
{
	this->start_time = start_time;
};


clock_t Animation::GetNextFrameTime()
{
	return next_frame_time;
};

void Animation::SetNextFrameTime(clock_t next_frame_time)
{
	this->next_frame_time = next_frame_time;
};


clock_t Animation::GetEndTime()
{
	return end_time;
};

void Animation::SetEndTime(clock_t end_time)
{
	this->end_time = end_time;
};

