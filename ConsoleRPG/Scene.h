#pragma once
#include "Player.h"
#include "Terrain.h"
#include "BufferQueueElement.h"

class Scene
{
private:
	Player player;
	Terrain terrain;
	
	std::vector<EntityAnimated> animated_entities;
	std::vector<EntityAnimated*> entity_pointers;

	std::vector<BufferQueueElement> buffer_queue;

public:
	Scene(Player player, std::string terrain_color_data_path, std::string terrain_hitbox_data_path, std::string terrain_shadow_data_path);
	void SetPointers();
	
	vector2i GetPlayerPosition();
	std::vector<BufferQueueElement>& GetBufferQueue();
	Frame& GetColorData();
	Frame& GetHitboxData();
	std::vector<vector2i>& GetShadowData();

	void UpdateBufferQueue();
	void UpdateEntities();
	void UpdateMovement();
	void Update();
};

