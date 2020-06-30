#include "Player.h"

void Player::InitialisePlayer()
{
    std::vector<std::string> running_animations_paths = { "../Files/Player/Running/running_right.txt",
                                                            "../Files/Player/Running/running_up.txt",
                                                            "../Files/Player/Running/running_left.txt",
                                                            "../Files/Player/Running/running_down.txt" };

    std::vector<std::string> attack1_animations_paths = { "../Files/Player/Attacks/Attack1/attack_right_1.txt",
                                                            "../Files/Player/Attacks/Attack1/attack_up_1.txt",
                                                            "../Files/Player/Attacks/Attack1/attack_left_1.txt",
                                                            "../Files/Player/Attacks/Attack1/attack_down_1.txt" };

    std::vector<std::string> attack2_animations_paths = { "../Files/Player/Attacks/Attack2/attack_right_2.txt",
                                                            "../Files/Player/Attacks/Attack2/attack_up_2.txt",
                                                            "../Files/Player/Attacks/Attack2/attack_left_2.txt",
                                                            "../Files/Player/Attacks/Attack2/attack_down_2.txt" };

    std::vector<std::string> attack3_animations_paths = { "../Files/Player/Attacks/Attack3/attack_right_3.txt",
                                                            "../Files/Player/Attacks/Attack3/attack_up_3.txt",
                                                            "../Files/Player/Attacks/Attack3/attack_left_3.txt",
                                                            "../Files/Player/Attacks/Attack3/attack_down_3.txt" };

    std::vector<std::string> attack4_animations_paths = { "../Files/Player/Attacks/Attack4/attack_right_4.txt",
                                                            "../Files/Player/Attacks/Attack4/attack_up_4.txt",
                                                            "../Files/Player/Attacks/Attack4/attack_left_4.txt",
                                                            "../Files/Player/Attacks/Attack4/attack_down_4.txt" };
    // Add animations to the animator
    {
        for (auto& path : running_animations_paths) { animator.AddAnimation(path); }

        for (auto& path : attack1_animations_paths) { animator.AddAnimation(path); }
        for (auto& path : attack2_animations_paths) { animator.AddAnimation(path); }
        for (auto& path : attack3_animations_paths) { animator.AddAnimation(path); }
        for (auto& path : attack4_animations_paths) { animator.AddAnimation(path); }
    }
    // Add nodes to the animator
    {
        animator.AddNode({ 4,5,6,7 }); // node 1, animations 4,5,6,7 - running

        animator.AddNode({ 8,9,10,11 }); // node 2, animations 8,9,10,11 - attack1
        animator.AddNode({ 12,13,14,15 }); // node 3, animations 12,13,14,15 - attack2
        animator.AddNode({ 16,17,18,19 }); // node 4, animations 16,17,18,19 - attack3
        animator.AddNode({ 20,21,22,23 }); // node 5, animations 20,21,22,23 - attack4
    }
    // Add animator variables
    {
        animator.AddInteger("horizontal", 0);
        animator.AddInteger("vertical", 0);
        animator.AddBoolean("running", false);
        animator.AddTrigger("attack", false);
    }
    // Configure connections and their conditions
    {
        animator.AddConnection(0, 1, false); // connection 0, idle -> running
        animator.AddConnectionConditionAND(0, "boolean", "running", "==", true);

        animator.AddConnection(1, 0, false); // connection 1, running -> idle
        animator.AddConnectionConditionAND(1, "boolean", "running", "==", false);

        animator.AddConnection(0, 2, false); // connection 2, idle -> attack1
        animator.AddConnectionConditionAND(2, "trigger", "attack", "==", true);
        animator.AddConnection(1, 2, false); // connection 3, running -> attack1
        animator.AddConnectionConditionAND(3, "trigger", "attack", "==", true);

        animator.AddConnection(2, 0, true); // connection 4, attack1 -> idle
        animator.AddConnectionConditionAND(4, "trigger", "attack", "==", false);
        animator.AddConnection(2, 3, true); // connection 5, attack1 -> attack2
        animator.AddConnectionConditionAND(5, "trigger", "attack", "==", true);

        animator.AddConnection(3, 0, true); // connection 6, attack2 -> idle
        animator.AddConnectionConditionAND(6, "trigger", "attack", "==", false);
        animator.AddConnection(3, 4, true); // connection 7, attack2 -> attack3
        animator.AddConnectionConditionAND(7, "trigger", "attack", "==", true);

        animator.AddConnection(4, 0, true); // connection 8, attack3 -> idle
        animator.AddConnectionConditionAND(8, "trigger", "attack", "==", false);
        animator.AddConnection(4, 5, true); // connection 9, attack3 -> attack4
        animator.AddConnectionConditionAND(9, "trigger", "attack", "==", true);

        animator.AddConnection(5, 0, true); // connection 10, attack4 -> idle
    }

    animator.SetActiveNode(0); // Set idle animation as active
    animator.SetInteger("horizontal", 0); animator.SetInteger("vertical", 1); // Have player forward downwards
}

Player::Player()
{

};

Player::Player(std::string idle_animation_path) : EntityAnimated(idle_animation_path)
{
	//Player player(idle_animations_paths);  node 0, animations 0,1,2,3 - idle
	InitialisePlayer();
}

Player::Player(std::vector<std::string> idle_animations_paths) : EntityAnimated(idle_animations_paths)
{
	//Player player(idle_animations_paths);  node 0, animations 0,1,2,3 - idle
	InitialisePlayer();
}

void Player::CheckForInput()
{
	next_move_cooldown = (clock_t)(CLOCKS_PER_SEC / move_speed);
	animator.SetBoolean("running", false);

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
