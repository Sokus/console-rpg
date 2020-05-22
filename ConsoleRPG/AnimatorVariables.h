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




