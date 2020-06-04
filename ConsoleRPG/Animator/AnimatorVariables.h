// This is custom Variable I made for Animator Tree. It lets you create variables that can be checked and compared by Animator Connections and used by Animator Conditions.
// Apart from standard types Bool, Float and String there is also new type Trigger, which is set to False after Condition it was used in was met. (look ConnectionCondition.h)

#pragma once
#include <string>

class AnimatorVariable
{
protected:
	std::string name = "";

public:
	AnimatorVariable(std::string name);

	std::string GetName();

	void SetName(std::string new_name);
};


class AnimatorBool : public AnimatorVariable
{
protected:
	bool value = false;
public:
	AnimatorBool(std::string name, bool value);

	bool GetValue();
	void SetValue(bool new_value);
};

class AnimatorTrigger : public AnimatorBool
{
public:
	AnimatorTrigger(std::string name, bool value);
};

class AnimatorInteger : public AnimatorVariable
{
	int value = 0;

public:
	AnimatorInteger(std::string name, int value);

	int GetValue();
	void SetValue(int new_value);
};




