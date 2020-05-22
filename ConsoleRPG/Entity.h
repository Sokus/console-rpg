#pragma once
#include <ctime>

#include "Containers.h"
#include "Hitbox.h"

class Entity
{
protected:
	int ID = 0;
	vector2i position = { 0,0 };
	vector2i move_direction = { 0,0 };
	float move_speed = 6;
	float attack_move_speed =2;
	clock_t next_move_time = 250;
	clock_t next_move_cooldown = 1000;

	std::vector<Hitbox> hitboxes;

	std::vector<BonusKeywords> bonuses;

public:
	Entity();
	int GetID();
	vector2i GetPosition();
	vector2i GetMoveDirection();

	void SetID(int ID);
	void SetPosition(vector2i new_position);
	void SetMoveDirection(vector2i new_move_direction);
	void SetNextMoveTime();

	// HITBOXES
	int GetHitboxCount();

	int GetHitboxID(int id);
	bool GetHitboxActive(int id);
	bool GetHitboxCinematic(int id);
	bool GetHitboxPlayerMade(int id);
	bool GeHitboxtDamaging(int id);
	int GetHitboxDamage(int id);
	const std::vector<BonusKeywords>& GetHitboxBonuses(int id);
	std::vector<vector2i> GetHitboxCorners(int id);
	Hitbox GetHitboxOffset(int id);

	void SetHitboxID(int id, int ID);
	void SetHitboxActive(int id, bool active);
	void SetHitboxCinematic(int id, bool cinematic);
	void SetHitboxPlayerMade(int id, bool player_made);
	void SetHitboxDamaging(int id, bool damaging);
	void SetHitboxDamage(int id, int damage);
	void SetHitboxBonuses(int id, const std::vector<BonusKeywords>& bonuses);
	void SetHitboxCorners(int id, std::vector<vector2i> corners);

	bool HitboxIntersect(int id, Hitbox hitbox);
	bool HitboxIntersect(int id, vector2i point);

	virtual void Update();

};

