#pragma once
#include <fstream>
#include <iostream>

#include "Frame.h"

class Terrain
{
private:
	std::string name;
	vector2i size = { 10,10 };

	Frame color_data;
	Frame hitbox_data;

	std::vector<vector2i> shadow_data;

public:
	Terrain();
	void ConstructorFunction(std::string color_data_path, std::string hitbox_data_path);
	Terrain(std::string color_data_path, std::string hitbox_data_path);
	Terrain(std::string color_data_path, std::string hitbox_data_path, std::string shadow_data_path);

	vector2i GetSize();
	Frame& GetColorData();
	Frame& GetHitboxData();
	std::vector<vector2i>& GetShadowData();

};

