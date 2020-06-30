#include "Entity/Player.h"
#include "Terrain.h"
#include "GFXE/BufferQueueElement.h"
#include "Scene.h"


class SceneManager
{
private:
    Player player;
    std::vector<Scene> scenes;
    int currentScene = 0;

public:
    SceneManager();

    void ChangeActiveScene(int newScene);

    vector2i GetPlayerPosition();
    std::vector<BufferQueueElement>& GetBufferQueue();
    Frame& GetColorData();
    std::vector<vector2i>& GetShadowData();

    void Update();
};
