#pragma once
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

#include "Frame.h"

class Animation
{
private:
	std::string name;
	vector2i size = { 0,0 };
	vector2i offset = { 0,0 };

	int number_of_frames = 0;
	int current_frame = 0;
	clock_t next_frame_time = 0;
	float frames_per_second = 1;

	clock_t start_time = 0;
	clock_t end_time = 0;

	bool loop = true;

	
	std::vector<Frame> frames;

public:
	Animation(std::string file_location);
	void Reset();
	void Update();
	bool GetLoop();
	void SetLoop(bool value);

	int GetCurrentFrameNumber();
	void SetCurrentFrameNumber(int frame_number);

	clock_t GetStartTime();
	void SetStartTime(clock_t start_time);

	clock_t GetNextFrameTime();
	void SetNextFrameTime(clock_t next_frame_time);

	clock_t GetEndTime();
	void SetEndTime(clock_t end_time);

	vector2i GetAnimOffset();
	Frame GetCurrentFrameObject();
};

