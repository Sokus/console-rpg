#pragma once
#include "Entity.h"
#include "Animator/Animator.h"

class EntityAnimated : public Entity
{
private:

public:
	Animator animator;

	EntityAnimated();
	EntityAnimated(std::string idle_animation_path);
	EntityAnimated(std::vector<std::string> idle_animations_paths);

	virtual void Update();
};

