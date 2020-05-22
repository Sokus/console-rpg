#include "AnimatorVariables.h"

AnimatorVariable::AnimatorVariable(std::string name) { this->name = name; };

AnimatorBool::AnimatorBool(std::string name, bool value) : AnimatorVariable::AnimatorVariable(name) { this->value = value; };

AnimatorTrigger::AnimatorTrigger(std::string name, bool value) : AnimatorBool::AnimatorBool(name, value) {};

AnimatorInteger::AnimatorInteger(std::string name, int value) : AnimatorVariable::AnimatorVariable(name) { this->value = value; };

std::string AnimatorVariable::GetName() { return name; };

bool AnimatorBool::GetValue()
{
	return value;
};

int AnimatorInteger::GetValue()
{
	return value;
};

void AnimatorVariable::SetName(std::string new_name)
{
	this->name = new_name;
};

void AnimatorBool::SetValue(bool new_value)
{
	this->value = new_value;
	
};

void AnimatorInteger::SetValue(int new_value)
{
	this->value = new_value;
};