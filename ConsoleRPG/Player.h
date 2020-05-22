#pragma once
#include "EntityAnimated.h"
#include <Windows.h>

class Player : public EntityAnimated
{

public:
	Player();
	Player(std::string idle_animation_path);
	Player(std::vector<std::string> idle_animations_paths);	
	void CheckForInput();

	void Update();
};

