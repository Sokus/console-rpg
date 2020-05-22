#include "AnimatorNode.h"

AnimatorNode::AnimatorNode(int ID)
{
	directional = false;
	animationIDs.emplace_back(ID);
};

AnimatorNode::AnimatorNode(std::vector<int> IDs)
{
	directional = true;
	for (int i = 0; i < 4; i++)
	{
		animationIDs.emplace_back(IDs[i]);
	}
};

bool AnimatorNode::GetActive()
{
	return this->active;
};

bool AnimatorNode::GetAnimationFinished()
{
	return this->animation_finished;
};

vector2i AnimatorNode::GetAnimationOffset(std::vector<Animation>& animations)
{
	return animations[animationIDs[active_animation]].GetAnimOffset();
};

clock_t AnimatorNode::GetAnimationStartTime(std::vector<Animation>& animations)
{
	return animations[animationIDs[active_animation]].GetStartTime();
};

clock_t AnimatorNode::GetAnimationEndTime(std::vector<Animation>& animations)
{
	return animations[animationIDs[active_animation]].GetEndTime();
};

void AnimatorNode::SetActive(bool value, std::vector<Animation>& animations)
{
	this->active = value;

	if (value)
	{
		animations[animationIDs[active_animation]].Reset();
		animation_finished = false;
	}
};

void AnimatorNode::SetAnimationFinished(bool value)
{
	this->animation_finished = value;
};

void AnimatorNode::Update(std::vector<AnimatorInteger>& integers, std::vector<Animation>& animations)
{
	if (active)
	{
		int new_active_animation = 0;

		if (directional)
		{
			int horizontal = 0;
			int vertical = 0;

			for (auto& element : integers)
			{
				if (element.GetName() == "horizontal")
				{
					horizontal = element.GetValue();
				}

				if (element.GetName() == "vertical")
				{
					vertical = element.GetValue();
				}
			}

			if (vertical == -1) new_active_animation = 1;
			if (vertical == 1) new_active_animation = 3;
			if (horizontal == 1) new_active_animation = 0;
			if (horizontal == -1) new_active_animation = 2;
		}

		if (new_active_animation != active_animation)
		{
			animations[animationIDs[new_active_animation]].SetCurrentFrameNumber(animations[animationIDs[active_animation]].GetCurrentFrameNumber());
			animations[animationIDs[new_active_animation]].SetStartTime(animations[animationIDs[active_animation]].GetStartTime());
			animations[animationIDs[new_active_animation]].SetNextFrameTime(animations[animationIDs[active_animation]].GetNextFrameTime());
			animations[animationIDs[new_active_animation]].SetEndTime(animations[animationIDs[active_animation]].GetEndTime());

			active_animation = new_active_animation;
		}


		if (last_frame != current_frame) last_frame = current_frame;


		if (animation_finished && animations[animationIDs[active_animation]].GetLoop())
		{
			animations[animationIDs[active_animation]].Reset();
		}

		animations[animationIDs[active_animation]].Update();
		if (clock() > animations[animationIDs[active_animation]].GetEndTime())
		{
			animation_finished = true;
		}
		else
		{
			animation_finished = false;
		}

		current_frame = animations[animationIDs[active_animation]].GetCurrentFrameNumber();
	}
};

int AnimatorNode::GetCurrentFrameNumber()
{
	return current_frame;
}

int AnimatorNode::GetLastFrameNumber()
{
	return last_frame;
}

Frame AnimatorNode::GetCurrentFrameObject(std::vector<Animation> & animations)
{
	return animations[animationIDs[active_animation]].GetCurrentFrameObject();
}