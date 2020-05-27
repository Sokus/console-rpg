// This class connects two animation nodes (look at AnimatorNode.h), it has set of conditions that need to be met in order to jump from one node to another.
// This class is a part of bigger structure I call Animator Tree, with many complex behaviours. I think you could call it a State Machine.

#pragma once
#include <vector>
#include <string>

#include "AnimatorNode.h"
#include "ConnectionCondition.h"

class AnimatorConnection
{
private:
	bool has_exit_time = true;

	int from_node;
	int to_node;

	std::vector<std::vector<ConnectionCondition>> conditions;
public:
	AnimatorConnection(int from_node, int to_node, bool has_exit_time);

	void AND(std::string type, std::string name, std::string condition, int value);
	void OR();

	void Update(std::vector<AnimatorBool>& booleans,
		std::vector<AnimatorTrigger>& triggers,
		std::vector<AnimatorInteger>& integers,
		std::vector<Animation>& animations,
		std::vector<AnimatorNode>& nodes);
};

