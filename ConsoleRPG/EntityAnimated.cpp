#include "EntityAnimated.h"

EntityAnimated::EntityAnimated()
{

};

EntityAnimated::EntityAnimated(std::string idle_animation_path)
{
	animator.AddAnimation(idle_animation_path);

	animator.AddNode((int)animator.GetAnimationsSize() - 1);

	animator.SetActiveNode(0);
};

EntityAnimated::EntityAnimated(std::vector<std::string> idle_animations_paths)
{
	for (int i = 0; i < 4; i++)
	{
		animator.AddAnimation(idle_animations_paths[i]);
	}

	animator.AddNode({ 0,1,2,3 });

	animator.SetActiveNode(0);
};

void EntityAnimated::Update()
{
	animator.Update();
}
