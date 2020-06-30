#pragma once
#include "Entity/Player.h"
#include "Terrain.h"
#include "GFXE/BufferQueueElement.h"

class Scene
{
private:
    Player* player;
	Terrain terrain;
	
	std::vector<EntityAnimated> animated_entities;
	std::vector<EntityAnimated*> entity_pointers;

	std::vector<BufferQueueElement> buffer_queue;

public:
    Scene(Player* player, std::string terrain_color_data_path, std::string terrain_hitbox_data_path, std::string terrain_shadow_data_path);
	void SetPointers();

	std::vector<BufferQueueElement>& GetBufferQueue();
    Frame& GetColorData();
	std::vector<vector2i>& GetShadowData();

    void AddEntityAnimated(const EntityAnimated& entityAnimated);

	void UpdateBufferQueue();
	void UpdateEntities();
	void UpdateMovement();
	void Update();
};

