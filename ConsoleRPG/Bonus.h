#pragma once
#include <vector>

enum class BonusKeywords
{
	Effective,
	Resistance,
	BonusHP,
	DmgToHP,

	Human,
	Animal,

};

struct Bonus
{
	float value;
	std::vector<BonusKeywords> keywords;
};

