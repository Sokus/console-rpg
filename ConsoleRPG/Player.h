// This class is very simmilar to EntityAnimated but it adds some sort of control over the player.

#pragma once
#include "EntityAnimated.h"
#include <Windows.h>

class Player : public EntityAnimated
{

public:
	Player();
	Player(std::string idle_animation_path);
	Player(std::vector<std::string> idle_animations_paths);	
	void InitialisePlayer();

	void CheckForInput();
	void Update();
};

