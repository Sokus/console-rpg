// This class is responsible for drawing images on the screen. It has two buffer arrays - front and back buffers - which hold all the pixel values.

#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "Containers.h"
#include "Frame.h"
#include "Terrain.h"

class GFXE
{
	int clearPixelID = 0;
	Pixel clearPixel;
	int minDepthValue = INT_MIN;

	vector2i camera_offset = { 0,0 };

	std::vector<std::vector<Pixel>> frontBuffer;
	std::vector<std::vector<Pixel>> backBuffer;

	std::vector<Pixel> possibleColors;

	std::vector<vector2i> shadowData;

	
public:
	vector2i resolution = { 50,40 };
	GFXE();
	GFXE(int resolutionX, int resolutionY);
	
	void Clear();
	void Fill(int pixelID);
	void SetCursorPosition(int x, int y);
	void WriteOnPosition(int pixelID, int depth, int x, int y, bool terrain);
	void SetCameraOffset(vector2i offset);
	void SetShadowData(const std::vector<vector2i>& shadowData);
	void ForceWriteOnPosition(int pixelID, int x, int y);
	void AddToBuffer(Frame texture, int x, int y, int depth, bool terrain);
	void Display();
	void DisplayPixel(Pixel pixel);
};

