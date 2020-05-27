#include <iostream>
#include <Windows.h>
#include <cmath>
#include <ctime>

#include "GFXE.h"
#include "EntityAnimated.h"
#include "Scene.h"

int main()
{
	GFXE window;

	std::vector<std::string> idle_animations_paths = { "Files/Player/Idle/idle_right.txt",
														"Files/Player/Idle/idle_up.txt",
														"Files/Player/Idle/idle_left.txt",
														"Files/Player/Idle/idle_down.txt" };
	Player player(idle_animations_paths);

	Scene test_scene(player, "Files/Maps/map02/map02_color_data.txt", "Files/Maps/map02/map02_hitbox_data.txt", "Files/Maps/map02/map02_shadow_data.txt");
	window.SetShadowData(test_scene.GetShadowData());

	float updatesPerSecond = 100;
	float framesPerSecond = 30;

	clock_t nextFrame = 0;
	clock_t nextUpdate = 0;

	while (true)
	{
		if (clock() > nextUpdate)
		{
			nextUpdate = clock() + CLOCKS_PER_SEC / updatesPerSecond;

			test_scene.Update();
			window.SetCameraOffset(test_scene.GetPlayerPosition());
		}

		if (clock() > nextFrame)
		{
			nextFrame = clock() + CLOCKS_PER_SEC / framesPerSecond;

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