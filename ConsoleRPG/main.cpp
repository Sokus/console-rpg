#include <iostream>
#include <Windows.h>
#include <cmath>
#include <ctime>

#include "GFXE/GFXE.h"
#include "Entity/EntityAnimated.h"
#include "Scene/SceneManager.h"

int main()
{

    GFXE window;
    SceneManager sceneManager;

    window.SetShadowData(sceneManager.GetShadowData());

    float updatesPerSecond = 1000;
    float framesPerSecond = 40;

    clock_t nextFrame = 0;
    clock_t nextUpdate = 0;

    while (true)
    {
        if (clock() > nextUpdate)
        {
            nextUpdate = clock() + (clock_t)((float)CLOCKS_PER_SEC / updatesPerSecond);

            sceneManager.Update();
            window.SetCameraOffset(sceneManager.GetPlayerPosition());
        }

        if (clock() > nextFrame)
        {
            nextFrame = clock() + (clock_t)((float)CLOCKS_PER_SEC / framesPerSecond);

            window.AddToBuffer(sceneManager.GetColorData(), 0, 0, INT_MIN, true);

            for (auto& buffer_queue_element : sceneManager.GetBufferQueue())
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
