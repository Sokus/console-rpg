// This class is used to descrive conditions needed for animation node connection to be activated (look at AnimatorConnection.h)

#pragma once
#include <vector>
#include <string>

#include "AnimatorVariables.h"

class ConnectionCondition
{
private:
	std::string type = "";
	std::string name = "";
	std::string condition = "";
	int value = 0;

	bool ConditionMet(const int& value1, std::string condition, const int& value2);

public:
	std::string GetType();
	std::string GetName();

	ConnectionCondition(std::string type, std::string name, std::string condition, int value);
	bool Check(std::vector<AnimatorBool>& booleans, std::vector<AnimatorTrigger>& triggers, std::vector<AnimatorInteger>& integers);
};

