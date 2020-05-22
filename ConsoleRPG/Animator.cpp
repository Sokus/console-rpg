#include "Animator.h"

void Animator::AddBoolean(std::string name, bool value)
{
	booleans.emplace_back(*(new AnimatorBool(name, value)));
};

void Animator::AddTrigger(std::string name, bool value)
{
	triggers.emplace_back(*(new AnimatorTrigger(name, value)));
};

void Animator::AddInteger(std::string name, int value)
{
	integers.emplace_back(*(new AnimatorInteger(name, value)));
};

bool Animator::GetBoolean(std::string name)
{
	for (auto& boolean : booleans)
	{
		if (boolean.GetName() == name)
		{
			return boolean.GetValue();
		}
	}
	return false;
};

bool Animator::GetTrigger(std::string name)
{
	for (auto& trigger : triggers)
	{
		if (trigger.GetName() == name)
		{
			return trigger.GetValue();
		}
	}
	return false;
};

int Animator::GetInteger(std::string name)
{
	for (auto& integer : integers)
	{
		if (integer.GetName() == name)
		{
			return integer.GetValue();
		}
	}
	return 0;
};

void Animator::SetBoolean(std::string name, bool value)
{
	for (auto& boolean : booleans)
	{
		if (boolean.GetName() == name)
		{
			boolean.SetValue(value);
		}
	}
};

void Animator::SetTrigger(std::string name, bool value)
{
	for (auto& trigger : triggers)
	{
		if (trigger.GetName() == name)
		{
			trigger.SetValue(value);
		}
	}
};

void Animator::SetInteger(std::string name, int value)
{
	for (auto& integer : integers)
	{
		if (integer.GetName() == name)
		{
			integer.SetValue(value);
		}
	}
};

void Animator::AddAnimation(std::string path)
{
	animations.emplace_back(*(new Animation(path)));
};

void Animator::AddNode(int ID)
{
	if (ID >= 0 && ID < animations.size())
	{
		nodes.emplace_back(*(new AnimatorNode(ID)));
	}
};

void Animator::AddNode(std::vector<int> IDs)
{
	nodes.emplace_back(*(new AnimatorNode(IDs)));
};

void Animator::AddConnection(int from_node_ID, int to_node_ID, bool has_exit_time)
{
	if (from_node_ID >= 0 && from_node_ID < nodes.size() && to_node_ID >= 0 && to_node_ID < nodes.size())
	{
		connections.emplace_back(*(new AnimatorConnection(from_node_ID, to_node_ID, has_exit_time)));
	}
};

void Animator::AddConnectionConditionOR(int connectionID)
{
	if (connectionID >= 0 && connectionID < connections.size())
	{
		connections[connectionID].OR();
	}
};

void Animator::AddConnectionConditionAND(int connectionID, std::string type, std::string name, std::string condition, int value)
{
	if (connectionID >= 0 && connectionID < connections.size())
	{
		connections[connectionID].AND(type, name, condition, value);
	}
};

bool Animator::GetNodeActive(int ID)
{
	if (ID >= 0 && ID < nodes.size())
	{
		return nodes[ID].GetActive();
	}
	return false;
};

clock_t Animator::GetAnimationStartTime()
{
	for (auto& node : nodes)
	{
		if (node.GetActive())
		{
			return node.GetAnimationStartTime(animations);
		}
	}
	return 0;
};



clock_t Animator::GetAnimationEndTime()
{
	for (auto& node : nodes)
	{
		if (node.GetActive())
		{
			return node.GetAnimationEndTime(animations);
		}
	}
	return 0;
};

size_t Animator::GetAnimationsSize()
{
	return animations.size();
};

vector2i Animator::GetAnimationOffset()
{
	for (auto& node : nodes)
	{
		if (node.GetActive())
		{
			return node.GetAnimationOffset(animations);
		}
	}
	return { 0,0 };
};

void Animator::SetActiveNode(int ID)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (i == ID)
		{
			nodes[i].SetActive(true, animations);
		}
		else
		{
			nodes[i].SetActive(false, animations);
		}

	}
};

void Animator::Update()
{
	for (auto& node : nodes)
	{
		node.Update(integers, animations);
	}

	for (auto& connection : connections)
	{
		connection.Update(booleans, triggers, integers, animations, nodes);
	}
};

int Animator::GetRecentFrameNumberUpdate()
{
	int current_frame_number;
	int last_frame_number;

	for (auto& node : nodes)
	{
		if (node.GetActive())
		{
			current_frame_number = node.GetCurrentFrameNumber();
			last_frame_number = node.GetLastFrameNumber();
			if (current_frame_number != last_frame_number)return current_frame_number;
		}
	}
	return -1;
};

Frame Animator::GetCurrentFrameObject()
{
	for (auto& node : nodes)
	{
		if (node.GetActive())
		{
			return node.GetCurrentFrameObject(animations);
		}
	}

	return *(new Frame(1, 1));
};