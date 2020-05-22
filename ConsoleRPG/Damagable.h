#pragma once
#include <ctime>
class Damagable
{
protected:
	bool alive = true;
	int hp = 5;

public:
	void TakeDamage(int amount)
	{
		hp -= amount;
		if (hp <= 0) alive = false;
	}

};

