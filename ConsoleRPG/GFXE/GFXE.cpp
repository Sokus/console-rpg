#include "GFXE.h"

GFXE::GFXE()
{
	std::vector<Pixel> temporaryVector;
	Pixel temporaryPixel;

	for (int y = 0; y < resolution.y; y++)
	{
		temporaryVector.emplace_back(temporaryPixel);
	}

	for (int x = 0; x < resolution.x; x++)
	{
		frontBuffer.emplace_back(temporaryVector);
		backBuffer.emplace_back(temporaryVector);
	}
	for (int i = 0; i < 16; i++)
	{
		possibleColors.emplace_back();

		possibleColors.back().id = (int)possibleColors.size() - 1;
		possibleColors.back().foreground = i;
		possibleColors.back().background = 0;
		possibleColors.back().sign = (char)219;
		possibleColors.back().depth = minDepthValue;
	}

	for (int i = 0; i < 256; i++)
	{
		int iForeground = i % 16;
		int iBackground = i / 16;
		if (iForeground == iBackground) continue;

		possibleColors.emplace_back();

		possibleColors.back().id = (int)possibleColors.size() - 1;
		possibleColors.back().foreground = iForeground;
		possibleColors.back().background = iBackground;
		float mix = 0.74f;
		possibleColors.back().sign = (char)178;
		possibleColors.back().depth = minDepthValue;
	}

	for (int i = 0; i < 256; i++)
	{
		int iForeground = i % 16;
		int iBackground = i / 16;
		if (iForeground == iBackground) continue;

		possibleColors.emplace_back();

		possibleColors.back().id = (int)possibleColors.size() - 1;
		possibleColors.back().foreground = iForeground;
		possibleColors.back().background = iBackground;
		float mix = 0.26f;
		possibleColors.back().sign = (char)177;
		possibleColors.back().depth = minDepthValue;
	}

	for (int i = 0; i < 256; i++)
	{
		int iForeground = i % 16;
		int iBackground = i / 16;
		if (iForeground == iBackground) continue;

		possibleColors.emplace_back();

		possibleColors.back().id = (int)possibleColors.size() - 1;
		possibleColors.back().foreground = iForeground;
		possibleColors.back().background = iBackground;
		float mix = 0.135f;
		possibleColors.back().sign = (char)176;
		possibleColors.back().depth = minDepthValue;
	}
	
	Pixel fillPixel = possibleColors[0];
	for (int i = 0; i < possibleColors.size(); i++)
	{
		if (possibleColors[i].id == clearPixelID)
		{
			clearPixel = possibleColors[i];
		}
	}

	GFXE::Clear();
}

GFXE::GFXE(int resolutionX, int resolutionY)
{
	resolution = { resolutionX,resolutionY };
	GFXE();
}

void GFXE::Clear()
{
	for (int x = 0; x < resolution.x; x++)
	{
		for (int y = 0; y < resolution.y; y++)
		{
			backBuffer[x][y] = clearPixel;
		}
	}
}

void GFXE::Fill(int pixelID)
{
	Pixel fillPixel = possibleColors[0];
	for (int i = 0; i < possibleColors.size(); i++)
	{
		if (possibleColors[i].id == pixelID)
		{
			fillPixel = possibleColors[i];
		}
	}

	for (int x = 0; x < resolution.x; x++)
	{
		for (int y = 0; y < resolution.y; y++)
		{
			backBuffer[x][y] = fillPixel;
		}
	}
}

void GFXE::SetCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void GFXE::WriteOnPosition(int pixelID, int depth, int x, int y, bool terrain)
{
	if (!terrain)
	{
		if (backBuffer[x][y].depth < depth)
		{
			if (pixelID >= 0 && pixelID < possibleColors.size())
			{
				backBuffer[x][y].id = possibleColors[pixelID].id;
				backBuffer[x][y].foreground = possibleColors[pixelID].foreground;
				backBuffer[x][y].background = possibleColors[pixelID].background;
				backBuffer[x][y].sign = possibleColors[pixelID].sign;
				backBuffer[x][y].depth = depth;
			}

			if (pixelID == -2 && backBuffer[x][y].depth == minDepthValue)
			{
				for (int i = 0; i < shadowData.size(); i++)
				{
					if (shadowData[i].x == backBuffer[x][y].id)
					{
						if (shadowData[i].y >= 0 && shadowData[i].y < possibleColors.size())
						{
							backBuffer[x][y].id = possibleColors[shadowData[i].y].id;
							backBuffer[x][y].foreground = possibleColors[shadowData[i].y].foreground;
							backBuffer[x][y].background = possibleColors[shadowData[i].y].background;
							backBuffer[x][y].sign = possibleColors[shadowData[i].y].sign;
							backBuffer[x][y].depth = minDepthValue + 1;
						}
						break;
					}
				}
			}
		}
	}
	else
	{
		if (pixelID >= 0 && pixelID < possibleColors.size())
		{
			backBuffer[x][y].id = possibleColors[pixelID].id;
			backBuffer[x][y].foreground = possibleColors[pixelID].foreground;
			backBuffer[x][y].background = possibleColors[pixelID].background;
			backBuffer[x][y].sign = possibleColors[pixelID].sign;
			backBuffer[x][y].depth = minDepthValue;
		}
	}
}

void GFXE::SetCameraOffset(vector2i offset)
{
	camera_offset = offset;
	camera_offset.x -= resolution.x / 2 - 1;
	camera_offset.y -= resolution.y / 2 - 1;
};

void GFXE::SetShadowData(const std::vector<vector2i>& shadowData)
{
	this->shadowData = shadowData;
};

void GFXE::ForceWriteOnPosition(int pixelID, int x, int y)
{
	Pixel fillPixel = possibleColors[0];
	for (int i = 0; i < possibleColors.size(); i++)
	{
		if (possibleColors[i].id == pixelID)
		{
			fillPixel = possibleColors[i];
		}
	}
	backBuffer[x][y] = fillPixel;
}

void GFXE::AddToBuffer(Frame texture, int x, int y, int depth, bool terrain)
{
	int tempy = 0;
	int tempx = 0;
	int pixel = 0;
	for (int iy = 0; iy < texture.GetSize().y; iy++)
	{
		for (int ix = 0; ix < texture.GetSize().x; ix++)
		{
			tempy = iy + y - camera_offset.y;
			tempx = ix + x - camera_offset.x;
			
			if (tempy >= 0 && tempy < resolution.y && tempx >= 0 && tempx < resolution.x)
			{
				pixel = texture.Read(ix, iy);
				WriteOnPosition(pixel, depth, tempx, tempy, terrain);
			}
		}
	}
};

void GFXE::Display()
{
	
	for (int x = 0; x < resolution.x; x++)
	{
		for (int y = 0; y < resolution.y; y++)
		{
			if (frontBuffer[x][y].id!=backBuffer[x][y].id)
			{
				frontBuffer[x][y].id = backBuffer[x][y].id;
				frontBuffer[x][y].sign = backBuffer[x][y].sign;
				frontBuffer[x][y].foreground = backBuffer[x][y].foreground;
				frontBuffer[x][y].background = backBuffer[x][y].background;
				frontBuffer[x][y].depth = backBuffer[x][y].depth;

				// { █ ▓ ▒ ░
				SetCursorPosition(2*x, y);
				DisplayPixel(frontBuffer[x][y]);
			}
			backBuffer[x][y] = clearPixel;
		}
	}
}

void GFXE::DisplayPixel(Pixel pixel)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, pixel.foreground + pixel.background * 16);
	std::cout << pixel.sign << pixel.sign;
	SetConsoleTextAttribute(hConsole, 15);
};

