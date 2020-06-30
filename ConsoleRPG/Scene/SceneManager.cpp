#include "SceneManager.h"

SceneManager::SceneManager()
{
    std::vector<std::string> idle_animations_paths = { "../Files/Player/Idle/idle_right.txt",
                                                       "../Files/Player/Idle/idle_up.txt",
                                                       "../Files/Player/Idle/idle_left.txt",
                                                       "../Files/Player/Idle/idle_down.txt" };
    this->player=*(new Player(idle_animations_paths));
    this->player.SetID(1);
    this->player.SetPosition({80,52});

    // Initialise Scene 0
    {
        scenes.emplace_back(*(new Scene(&player, "../Files/Maps/map02/map02_color_data.txt",
                                        "../Files/Maps/map02/map02_hitbox_data.txt",
                                        "../Files/Maps/map02/map02_shadow_data.txt")));

        EntityAnimated tree("../Files/pink_tree.txt");
        {
            tree.SetID(2);
            tree.SetHitboxCorners(0, { {-1,0},{2,0} });
            tree.SetPosition({ 52,45 });
            scenes.back().AddEntityAnimated(tree);

            tree.SetPosition({ 111,40 });
            scenes.back().AddEntityAnimated(tree);

            tree.SetPosition({ 116,74 });
            scenes.back().AddEntityAnimated(tree);

            tree.SetPosition({ 55,128 });
            scenes.back().AddEntityAnimated(tree);
        }

        EntityAnimated tree_flipped("../Files/pink_tree_flipped.txt");
        {
            tree_flipped.SetID(2);
            tree_flipped.SetHitboxCorners(0, { {-1,0},{2,0} });
            tree_flipped.SetPosition({ 85,37 });
            scenes.back().AddEntityAnimated(tree_flipped);

            tree_flipped.SetPosition({ 80,72 });
            scenes.back().AddEntityAnimated(tree_flipped);

            tree_flipped.SetPosition({ 34,66 });
            scenes.back().AddEntityAnimated(tree_flipped);
        }
    }

    // Initialise Scene 1
    {
        scenes.emplace_back(*(new Scene(&player, "../Files/Maps/map02/map02_color_data.txt",
                                        "../Files/Maps/map02/map02_hitbox_data.txt",
                                        "../Files/Maps/map02/map02_shadow_data.txt")));

        EntityAnimated tree("../Files/pink_tree.txt");
        tree.SetPosition({ 65,45 });
        tree.SetID(2);
        tree.SetHitboxCorners(0, { {-1,0},{2,1} });
        scenes.back().AddEntityAnimated(tree);
    }
}

void SceneManager::ChangeActiveScene(int newScene)
{
    if(newScene>=0 && newScene < scenes.size())
    {
        currentScene = newScene;
        Update();
    }
}

vector2i SceneManager::GetPlayerPosition()
{
    return player.GetPosition();
}

std::vector<BufferQueueElement> &SceneManager::GetBufferQueue()
{
    return scenes[currentScene].GetBufferQueue();
}

Frame &SceneManager::GetColorData()
{
    return scenes[currentScene].GetColorData();
}

std::vector<vector2i> &SceneManager::GetShadowData()
{
    return scenes[currentScene].GetShadowData();
}

void SceneManager::Update()
{
    scenes[currentScene].Update();
}
