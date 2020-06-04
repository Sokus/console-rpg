// This class is a part of Animator Tree, it holds its own animation (or 4 animations, if its directional).
// For Animator Node to be active it needs to be activated manually or by Animator Connection.

#pragma once
#include "AnimatorVariables.h"
#include "Animation.h"
class AnimatorNode
{
private:
	bool active = false;
	bool animation_finished = false;
	bool directional = false;

	int active_animation = 0;
	std::vector<int> animationIDs;

	int last_frame = 0;
	int current_frame = 0;

public:
	AnimatorNode(int ID);
	AnimatorNode(std::vector<int> IDs);

	bool GetActive();
	bool GetAnimationFinished();
	vector2i GetAnimationOffset(std::vector<Animation>& animations);
	clock_t GetAnimationStartTime(std::vector<Animation>& animations);
	clock_t GetAnimationEndTime(std::vector<Animation>& animations);

	void SetActive(bool value, std::vector<Animation>& animations);
	void SetAnimationFinished(bool value);

	void Update(std::vector<AnimatorInteger>& integers, std::vector<Animation>& animations);

	int GetLastFrameNumber();
	int GetCurrentFrameNumber();

	Frame GetCurrentFrameObject(std::vector<Animation>& animations);
};

