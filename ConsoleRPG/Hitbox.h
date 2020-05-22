#pragma once
#include "Containers.h"
#include "Bonus.h"

class Hitbox
{
protected:
	int ID = 0;
	bool active = false;

	bool cinematic = true;
	std::vector<vector2i> corners = { {-1,-1},{1,1} };
	
	bool player_made = false;
	bool damaging = false;
	int damage = 0;
	std::vector<BonusKeywords> bonuses;


	bool Intersect(Hitbox first, Hitbox second);
	bool Intersect(vector2i point, Hitbox second);

public:
	int GetID();
	bool GetActive();
	bool GetCinematic();
	bool GetPlayerMade();
	bool GetDamaging();
	int GetDamage();
	const std::vector<BonusKeywords>& GetBonuses();
	std::vector<vector2i> GetCorners();

	void SetID(int ID);
	void SetActive(bool active);
	void SetCinematic(bool cinematic);
	void SetPlayerMade(bool player_made);
	void SetDamaging(bool damaging);
	void SetDamage(int damage);
	void SetBonuses(const std::vector<BonusKeywords>& bonuses);
	void SetCorners(std::vector<vector2i> corners);

	bool Intersect(Hitbox hitbox, vector2i position);
	bool Intersect(vector2i point, vector2i position);

	Hitbox Offset(vector2i position);
};

