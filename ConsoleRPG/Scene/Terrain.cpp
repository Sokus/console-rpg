#include "Terrain.h"

Terrain::Terrain()
{

};

void Terrain::ConstructorFunction(std::string color_data_path, std::string hitbox_data_path)
{
	std::ifstream file;
	file.open(color_data_path);
	if (!file)
	{
		std::cout << "Unable to open " << color_data_path << std::endl;
	}
	else
	{
		file >> name >> size.x >> size.y;
		//std::cout << name << " " << size.x << " " << size.y << "\n";
		color_data = *(new Frame(size.x, size.y));

		int temporary_value = 0;

		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
			{
				file >> temporary_value;
				//std::cout << temporary_value << " ";
				color_data.Write(temporary_value, x, y);
			}
			//std::cout << "\n";
		}
	}
	file.close();

	file.open(hitbox_data_path);
	if (!file)
	{
		std::cout << "Unable to open " << color_data_path << std::endl;
	}
	else
	{
		std::string temporary_name;
		int temporary_x;
		int temporary_y;
		file >> temporary_name >> temporary_x >> temporary_y;
		//std::cout << temporary_name << " " << temporary_x << " " << temporary_y << "\n";
		if (name != temporary_name || size.x != temporary_x || size.y != temporary_y)
		{
			std::cout << "Values do not match in " << hitbox_data_path << std::endl;
			return;
		}

		hitbox_data = *(new Frame(size.x, size.y));

		int temporary_value = 0;

		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
			{
				file >> temporary_value;
				//std::cout << temporary_value << " ";
				hitbox_data.Write(temporary_value, x, y);
			}
			//std::cout << "\n";
		}
	}
	file.close();
};


Terrain::Terrain(std::string color_data_path, std::string hitbox_data_path)
{
	ConstructorFunction(color_data_path, hitbox_data_path);
};

Terrain::Terrain(std::string color_data_path, std::string hitbox_data_path, std::string shadow_data_path)
{
	ConstructorFunction(color_data_path, hitbox_data_path);

	std::ifstream file;
	file.open(shadow_data_path);
	if (!file)
	{
		std::cout << "Unable to open " << shadow_data_path << std::endl;
	}
	else
	{
		int temporary_size;
		file >> name >> temporary_size;

		int temporary_value1 = 0;
		int temporary_value2 = 0;

		for (int i = 0; i < temporary_size; i++)
		{
			file >> temporary_value1 >> temporary_value2;
			vector2i temporary_vector = { temporary_value1, temporary_value2 };
			shadow_data.emplace_back(temporary_vector);
		}
	}
	file.close();
};

vector2i Terrain::GetSize()
{
	return size;
};

Frame& Terrain::GetColorData()
{
	return color_data;
};

Frame& Terrain::GetHitboxData()
{
	return hitbox_data;
};

std::vector<vector2i>& Terrain::GetShadowData()
{
	return shadow_data;
};