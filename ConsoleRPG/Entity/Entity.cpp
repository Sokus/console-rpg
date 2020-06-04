#include "Entity.h"

Entity::Entity()
{
	Hitbox new_hitbox;
	new_hitbox.SetID(this->ID);
	new_hitbox.SetActive(true);
	new_hitbox.SetCinematic(false);
	new_hitbox.SetDamaging(false);
	new_hitbox.SetPlayerMade(false);
	new_hitbox.SetCorners({ {-1,-1},{1,1} });

	hitboxes.emplace_back(new_hitbox);
};

int Entity::GetID()
{
	return this->ID;
};

vector2i Entity::GetPosition()
{
	return position;
};

vector2i Entity::GetMoveDirection()
{
	return move_direction;
};

void Entity::SetID(int ID)
{
	this->ID = ID;
}

void Entity::SetPosition(vector2i new_position)
{
	this->position = new_position;
};

void Entity::SetMoveDirection(vector2i new_move_direction)
{
	this->move_direction = new_move_direction;
};

void Entity::SetNextMoveTime()
{
	this->next_move_time = clock() + next_move_cooldown;
};

int Entity::GetHitboxCount()
{
	return (int)hitboxes.size();
};

int Entity::GetHitboxID(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].GetID();
	}
	return 0;
}

bool Entity::GetHitboxActive(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].GetActive();
	}
	return false;
};

bool Entity::GetHitboxCinematic(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].GetCinematic();
	}
	return false;
};

bool Entity::GetHitboxPlayerMade(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].GetPlayerMade();
	}
	return false;
};

bool Entity::GeHitboxtDamaging(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].GetDamaging();
	}
	return false;
};

int Entity::GetHitboxDamage(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].GetDamage();
	}
	return 0;
};

const std::vector<BonusKeywords>& Entity::GetHitboxBonuses(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].GetBonuses();
	}
	std::vector<BonusKeywords> temp;
	return temp;
};

std::vector<vector2i> Entity::GetHitboxCorners(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].GetCorners();
	}
	std::vector<vector2i> temp;
	return temp;
};

Hitbox Entity::GetHitboxOffset(int id)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].Offset(this->position);
	}
	Hitbox temp;
	return temp;
};

void Entity::SetHitboxID(int id, int ID)
{
	if (id >= 0 && id < hitboxes.size())
	{
		hitboxes[id].SetID(ID);
	}
}

void Entity::SetHitboxActive(int id, bool active)
{
	if (id >= 0 && id < hitboxes.size())
	{
		hitboxes[id].SetActive(active);
	}
};

void Entity::SetHitboxCinematic(int id, bool cinematic)
{
	if (id >= 0 && id < hitboxes.size())
	{
		hitboxes[id].SetCinematic(cinematic);
	}
};

void Entity::SetHitboxPlayerMade(int id, bool player_made)
{
	if (id >= 0 && id < hitboxes.size())
	{
		hitboxes[id].SetPlayerMade(player_made);
	}
};

void Entity::SetHitboxDamaging(int id, bool damaging)
{
	if (id >= 0 && id < hitboxes.size())
	{
		hitboxes[id].SetDamaging(damaging);
	}
};

void Entity::SetHitboxDamage(int id, int damage)
{
	if (id >= 0 && id < hitboxes.size())
	{
		hitboxes[id].SetDamage(damage);
	}
};

void Entity::SetHitboxBonuses(int id, const std::vector<BonusKeywords>& bonuses)
{
	if (id >= 0 && id < hitboxes.size())
	{
		hitboxes[id].SetBonuses(bonuses);
	}
};

void Entity::SetHitboxCorners(int id, std::vector<vector2i> corners)
{
	if (id >= 0 && id < hitboxes.size())
	{
		hitboxes[id].SetCorners(corners);
	}
};

bool Entity::HitboxIntersect(int id, Hitbox hitbox)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].Intersect(hitbox, this->position);
	}
	return false;
};

bool Entity::HitboxIntersect(int id, vector2i point)
{
	if (id >= 0 && id < hitboxes.size())
	{
		return hitboxes[id].Intersect(point, this->position);
	}
	return false;
};

void Entity::Update()
{

};


