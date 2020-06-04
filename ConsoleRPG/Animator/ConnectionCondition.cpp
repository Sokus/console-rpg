#include "ConnectionCondition.h"

ConnectionCondition::ConnectionCondition(std::string type, std::string name, std::string condition, int value)
{
	this->type = type;
	this->name = name;
	this->condition = condition;
	this->value = value;
};

bool ConnectionCondition::ConditionMet(const int& value1, std::string condition, const int& value2)
{

	if (condition == "==")
	{
		return value1 == value2;
	}
	if (condition == "!=")
	{
		return value1 != value2;
	}	
	if (condition == "<")
	{
		return value1 < value2;
	}
	if (condition == "<=")
	{
		return value1 <= value2;
	}
	if (condition == ">")
	{
		return value1 > value2;
	}
	if (condition == ">=")
	{
		return value1 >= value2;
	}
	return false;
};

bool ConnectionCondition::Check(std::vector<AnimatorBool>& booleans, std::vector<AnimatorTrigger>& triggers, std::vector<AnimatorInteger>& integers)
{
	if (this->type == "boolean")
	{
		for (auto& element : booleans)
		{
			if (element.GetName() == this->name)
			{
				return ConditionMet(element.GetValue(), this->condition, this->value);
			}
		}
		
	}

	if (this->type == "trigger")
	{
		for (auto& element : triggers)
		{
			if (element.GetName() == this->name)
			{
				return ConditionMet(element.GetValue(), this->condition, this->value);
			}
		}
	}

	if (this->type == "integer")
	{
		for (auto& element : integers)
		{
			if (element.GetName() == this->name)
			{
				return ConditionMet(element.GetValue(), this->condition, this->value);
			}
		}
	}

	return false;
};

std::string ConnectionCondition::GetType()
{
	return this->type;
};
std::string ConnectionCondition::GetName()
{
	return this->name;
};
