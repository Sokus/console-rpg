#include "AnimatorConnection.h"
#include "AnimatorVariables.h"

AnimatorConnection::AnimatorConnection(int from_node, int to_node, bool has_exit_time)
{
	this->from_node = from_node;
	this->to_node = to_node;
	this->has_exit_time = has_exit_time;
}

void AnimatorConnection::AND(std::string type, std::string name, std::string condition, int value)
{
	if (conditions.size() == 0)
	{
		std::vector<ConnectionCondition> temporary;
		conditions.emplace_back(temporary);
	}

	ConnectionCondition temporaryConnection(type, name, condition, value);
	conditions.back().emplace_back(temporaryConnection);
};

void AnimatorConnection::OR()
{
	std::vector<ConnectionCondition> temporary;
	conditions.emplace_back(temporary);
};

void AnimatorConnection::Update(std::vector<AnimatorBool>& booleans,
	std::vector<AnimatorTrigger>& triggers,
	std::vector<AnimatorInteger>& integers,
	std::vector<Animation>& animations,
	std::vector<AnimatorNode>& nodes)
{
	if (nodes[from_node].GetActive())
	{
		if (has_exit_time && !nodes[from_node].GetAnimationFinished())
		{
			return;
		}

		bool conditions_met = true;
		if (conditions.size() > 0)
		{
			for (auto& or_element : conditions)
			{
				conditions_met = true;

				std::vector<std::string> trigger_names;
				trigger_names.clear();

				for (auto& and_element : or_element)
				{
					bool check_value = and_element.Check(booleans, triggers, integers);
					if (check_value && and_element.GetType() == "trigger")
					{
						trigger_names.emplace_back(and_element.GetName());
					}

					if (!check_value) conditions_met = false;
				}

				if (conditions_met)
				{
					if (trigger_names.size()>0)
					{
						for (auto& trigger : triggers)
						{
							for (auto& trigger_name : trigger_names)
							{
								if (trigger.GetName() == trigger_name)
								{
									trigger.SetValue(false);
								}
							}
						}
					}

					break;
				}
			}
		}

		if (conditions_met)
		{
			nodes[from_node].SetActive(false, animations);
			nodes[to_node].SetActive(true, animations);
		}
	}
};