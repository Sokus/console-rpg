#include "Player.h"

Player::Player()
{

};

Player::Player(std::string idle_animation_path) : EntityAnimated(idle_animation_path)
{

}

Player::Player(std::vector<std::string> idle_animations_paths) : EntityAnimated(idle_animations_paths)
{

}

void Player::CheckForInput()
{
	next_move_cooldown = (clock_t)(CLOCKS_PER_SEC / move_speed);
	animator.SetBoolean("running", false);

	bool animation_just_started = clock() > animator.GetAnimationStartTime() && clock() < animator.GetAnimationStartTime() + 5;
	bool animation_near_end = clock() > animator.GetAnimationEndTime() - 5 && clock() < animator.GetAnimationEndTime();
	bool any_attack_node_active = animator.GetNodeActive(2) || animator.GetNodeActive(3) || animator.GetNodeActive(4) || animator.GetNodeActive(5);

	vector2i input = { 0,0 };
	if (!any_attack_node_active || animation_near_end)
	{
		if (GetAsyncKeyState('D'))
		{
			input.x++;
		}
		if (GetAsyncKeyState('W'))
		{
			input.y--;
		}
		if (GetAsyncKeyState('A'))
		{
			input.x--;
		}
		if (GetAsyncKeyState('S'))
		{
			input.y++;
		}
	}
	
	if (!any_attack_node_active)
	{
		if (!GetAsyncKeyState(VK_SPACE))
		{
			if (input.x != 0 || input.y != 0)
			{
				animator.SetInteger("horizontal", input.x);
				animator.SetInteger("vertical", input.y);
				animator.SetBoolean("running", true);
				move_direction = { 0,0 };
				if (clock() > next_move_time)
				{
					if (input.x != 0)
					{
						move_direction.x = input.x;
					}
					else
					{
						move_direction.y = input.y;
					}
				}
			}
			else
			{
				animator.SetBoolean("running", false);
			}
		}
		else
		{
				animator.SetTrigger("attack", true);
		}
	}

	if (any_attack_node_active)
	{
		next_move_cooldown = CLOCKS_PER_SEC / attack_move_speed;
		if (animation_near_end)
		{
			if (GetAsyncKeyState(VK_SPACE))
			{
				animator.SetTrigger("attack", true);
			}
			if (input.x != 0 || input.y != 0)
			{
				animator.SetInteger("horizontal", input.x);
				animator.SetInteger("vertical", input.y);
			}
		}
		move_direction = { 0,0 };
		if (clock() > next_move_time)
		{
			int temp = animator.GetInteger("horizontal");
			if (temp != 0)
			{
				move_direction.x = temp;
			}
			else
			{
				move_direction.y = animator.GetInteger("vertical");
			}
		}
	}
};

void Player::Update()
{
	animator.Update();
	CheckForInput();
};