// This class is a heart of Animator Tree, it uses AnimatorVariables.h, AnimatorNode.h and AnimatorConnection.h to manage which animation is played and when. 
// You can set whatever conditions you want to whatever animations you have, you can add them on the fly (although you can't delete them).

#pragma once
#include <vector>
#include <string>

#include "AnimatorVariables.h"
#include "AnimatorNode.h"
#include "AnimatorConnection.h"

class Animator
{
private:
	std::vector<AnimatorBool> booleans;
	std::vector<AnimatorTrigger> triggers;
	std::vector<AnimatorInteger> integers;

	std::vector<Animation> animations;
	std::vector<AnimatorNode> nodes;
	std::vector<AnimatorConnection> connections;

public:
	void AddBoolean(std::string name, bool value);
	void AddTrigger(std::string name, bool value);
	void AddInteger(std::string name, int value);

	bool GetBoolean(std::string name);
	bool GetTrigger(std::string name);
	int GetInteger(std::string name);

	void SetBoolean(std::string name, bool value);
	void SetTrigger(std::string name, bool value);
	void SetInteger(std::string name, int value);

	void AddAnimation(std::string path);
	void AddNode(int ID);
	void AddNode(std::vector<int> IDs);
	void AddConnection(int from_node_ID, int to_node_ID, bool has_exit_time);
	void AddConnectionConditionOR(int connectionID);
	void AddConnectionConditionAND(int connectionID, std::string type, std::string name, std::string condition, int value);

	bool GetNodeActive(int ID);

	clock_t GetAnimationStartTime();
	clock_t GetAnimationEndTime();
	size_t GetAnimationsSize();
	vector2i GetAnimationOffset();

	void SetActiveNode(int ID);

	void Update();

	int GetRecentFrameNumberUpdate();

	Frame GetCurrentFrameObject();

};

