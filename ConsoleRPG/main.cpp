#include <iostream>
#include <Windows.h>
#include <cmath>
#include <ctime>

#include "GFXE.h"
#include "EntityAnimated.h"
#include "Scene.h"

Player InitialisePlayer()
{
	std::vector<std::string> idle_animations_paths = { "Files/Player/Idle/idle_right.txt",
														"Files/Player/Idle/idle_up.txt",
														"Files/Player/Idle/idle_left.txt",
														"Files/Player/Idle/idle_down.txt" };

	std::vector<std::string> running_animations_paths = { "Files/Player/Running/running_right.txt",
															"Files/Player/Running/running_up.txt",
															"Files/Player/Running/running_left.txt",
															"Files/Player/Running/running_down.txt" };

	std::vector<std::string> attack1_animations_paths = { "Files/Player/Attacks/Attack1/attack_right_1.txt",
															"Files/Player/Attacks/Attack1/attack_up_1.txt",
															"Files/Player/Attacks/Attack1/attack_left_1.txt",
															"Files/Player/Attacks/Attack1/attack_down_1.txt" };

	std::vector<std::string> attack2_animations_paths = { "Files/Player/Attacks/Attack2/attack_right_2.txt",
															"Files/Player/Attacks/Attack2/attack_up_2.txt",
															"Files/Player/Attacks/Attack2/attack_left_2.txt",
															"Files/Player/Attacks/Attack2/attack_down_2.txt" };

	std::vector<std::string> attack3_animations_paths = { "Files/Player/Attacks/Attack3/attack_right_3.txt",
															"Files/Player/Attacks/Attack3/attack_up_3.txt",
															"Files/Player/Attacks/Attack3/attack_left_3.txt",
															"Files/Player/Attacks/Attack3/attack_down_3.txt" };

	std::vector<std::string> attack4_animations_paths = { "Files/Player/Attacks/Attack4/attack_right_4.txt",
															"Files/Player/Attacks/Attack4/attack_up_4.txt",
															"Files/Player/Attacks/Attack4/attack_left_4.txt",
															"Files/Player/Attacks/Attack4/attack_down_4.txt" };

	Player player(idle_animations_paths); // node 0, animations 0,1,2,3 - idle

	for (auto& path : running_animations_paths) { player.animator.AddAnimation(path); }

	for (auto& path : attack1_animations_paths) { player.animator.AddAnimation(path); }
	for (auto& path : attack2_animations_paths) { player.animator.AddAnimation(path); }
	for (auto& path : attack3_animations_paths) { player.animator.AddAnimation(path); }
	for (auto& path : attack4_animations_paths) { player.animator.AddAnimation(path); }

	player.animator.AddNode({ 4,5,6,7 }); // node 1, animations 4,5,6,7 - running

	player.animator.AddNode({ 8,9,10,11 }); // node 2, animations 8,9,10,11 - attack1
	player.animator.AddNode({ 12,13,14,15 }); // node 3, animations 12,13,14,15 - attack2
	player.animator.AddNode({ 16,17,18,19 }); // node 4, animations 16,17,18,19 - attack3
	player.animator.AddNode({ 20,21,22,23 }); // node 5, animations 20,21,22,23 - attack4


	player.animator.AddInteger("horizontal", 0);
	player.animator.AddInteger("vertical", 0);
	player.animator.AddBoolean("running", false);
	player.animator.AddTrigger("attack", false);

	player.animator.AddConnection(0, 1, false); // connection 0, idle -> running
	player.animator.AddConnectionConditionAND(0, "boolean", "running", "==", true);

	player.animator.AddConnection(1, 0, false); // connection 1, running -> idle
	player.animator.AddConnectionConditionAND(1, "boolean", "running", "==", false);

	player.animator.AddConnection(0, 2, false); // connection 2, idle -> attack1
	player.animator.AddConnectionConditionAND(2, "trigger", "attack", "==", true);
	player.animator.AddConnection(1, 2, false); // connection 3, running -> attack1
	player.animator.AddConnectionConditionAND(3, "trigger", "attack", "==", true);

	player.animator.AddConnection(2, 0, true); // connection 4, attack1 -> idle
	player.animator.AddConnectionConditionAND(4, "trigger", "attack", "==", false);
	player.animator.AddConnection(2, 3, true); // connection 5, attack1 -> attack2
	player.animator.AddConnectionConditionAND(5, "trigger", "attack", "==", true);

	player.animator.AddConnection(3, 0, true); // connection 6, attack2 -> idle
	player.animator.AddConnectionConditionAND(6, "trigger", "attack", "==", false);
	player.animator.AddConnection(3, 4, true); // connection 7, attack2 -> attack3
	player.animator.AddConnectionConditionAND(7, "trigger", "attack", "==", true);

	player.animator.AddConnection(4, 0, true); // connection 8, attack3 -> idle
	player.animator.AddConnectionConditionAND(8, "trigger", "attack", "==", false);
	player.animator.AddConnection(4, 5, true); // connection 9, attack3 -> attack4
	player.animator.AddConnectionConditionAND(9, "trigger", "attack", "==", true);

	player.animator.AddConnection(5, 0, true); // connection 10, attack4 -> idle

	player.animator.SetActiveNode(0);
	player.SetPosition({ 70,60 });

	return player;
}

int main()
{
	GFXE window;

	Scene test_scene(InitialisePlayer(), "Files/Maps/map02/map02_color_data.txt", "Files/Maps/map02/map02_hitbox_data.txt", "Files/Maps/map02/map02_shadow_data.txt");
	window.SetShadowData(test_scene.GetShadowData());

	clock_t nextFrame = 0;
	clock_t nextUpdate = 0;
	
	while (true)
	{
		if (clock() > nextUpdate)
		{
			nextUpdate = clock() + 1;	
			
			test_scene.Update();
			window.SetCameraOffset(test_scene.GetPlayerPosition());
		}

		if (clock() > nextFrame)
		{
			nextFrame = clock() + 50;
			
			window.AddToBuffer(test_scene.GetColorData(), 0, 0, INT_MIN, true);

			for (auto& buffer_queue_element : test_scene.GetBufferQueue())
			{
				vector2i temporary = buffer_queue_element.GetPosition();
				window.AddToBuffer(buffer_queue_element.GetFrame(), temporary.x, temporary.y, buffer_queue_element.GetDepth(), false);
			}


			window.Display();
		}
	}

	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return 0;
}