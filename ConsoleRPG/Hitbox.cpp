#include "Hitbox.h"

int Hitbox::GetID()
{
	return this->ID;
};

bool Hitbox::GetActive()
{
	return active;
};

bool Hitbox::GetCinematic()
{
	return cinematic;
};

bool Hitbox::GetPlayerMade()
{
	return player_made;
};

bool Hitbox::GetDamaging()
{
	return damaging;
};

int Hitbox::GetDamage()
{
	return damage;
};

const std::vector<BonusKeywords>& Hitbox::GetBonuses()
{
	return bonuses;
};

std::vector<vector2i> Hitbox::GetCorners()
{
	return corners;
};

void Hitbox::SetID(int ID)
{
	this->ID = ID;
};

void Hitbox::SetActive(bool active)
{
	this->active = active;
};

void Hitbox::SetCinematic(bool cinematic)
{
	this->cinematic = cinematic;
};

void Hitbox::SetPlayerMade(bool player_made)
{
	this->player_made = player_made;
};

void Hitbox::SetDamaging(bool damaging)
{
	this->damaging = damaging;
};

void Hitbox::SetDamage(int damage)
{
	this->damage = damage;
};

void Hitbox::SetBonuses(const std::vector<BonusKeywords>& bonuses)
{
	this->bonuses = bonuses;
};

void Hitbox::SetCorners(std::vector<vector2i> corners)
{
	this->corners[0] = corners[0];
	this->corners[1] = corners[1];
};

bool Hitbox::Intersect(Hitbox first, Hitbox second)
{
	std::vector<vector2i> first_corners = first.GetCorners();
	std::vector<vector2i> second_corners = second.GetCorners();
	
	if (Intersect(first_corners[0], second)) return true;
	if (Intersect({ first_corners[0].x,first_corners[1].y }, second)) return true;
	if (Intersect(first_corners[1], second)) return true;
	if (Intersect({ first_corners[1].x,first_corners[0].y }, second)) return true;
	
	if (Intersect(second_corners[0], first)) return true;
	if (Intersect({ second_corners[0].x,second_corners[1].y }, first)) return true;
	if (Intersect(second_corners[1], first)) return true;
	if (Intersect({ second_corners[1].x,second_corners[0].y }, first)) return true;

	return false;
};

bool Hitbox::Intersect(vector2i point, Hitbox second)
{
	std::vector<vector2i> second_corners = second.GetCorners();
	return (point.x >= second_corners[0].x && point.x <= second_corners[1].x && point.y >= second_corners[0].y && point.y <= second_corners[1].y);
};

bool Hitbox::Intersect(Hitbox hitbox, vector2i position)
{
	Hitbox temporary;
	temporary.SetCorners({ {this->corners[0].x + position.x,this->corners[0].y + position.y }, {this->corners[1].x + position.x,this->corners[1].y + position.y} });
	return Intersect(temporary, hitbox);
};

bool Hitbox::Intersect(vector2i point, vector2i position)
{
	Hitbox temporary;
	temporary.SetCorners({ {this->corners[0].x + position.x,this->corners[0].y + position.y }, {this->corners[1].x + position.x,this->corners[1].y + position.y} });
	return Intersect(point, temporary);
};

Hitbox Hitbox::Offset(vector2i position)
{
	Hitbox temporary;
	temporary.SetCorners({ {this->corners[0].x + position.x,this->corners[0].y + position.y }, {this->corners[1].x + position.x,this->corners[1].y + position.y} });
	return temporary;
}