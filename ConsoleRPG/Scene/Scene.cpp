#include "Scene.h"

Scene::Scene(Player* player, std::string terrain_color_data_path, std::string terrain_hitbox_data_path, std::string terrain_shadow_data_path)
{
	this->player = player;
	this->terrain = *(new Terrain(terrain_color_data_path, terrain_hitbox_data_path, terrain_shadow_data_path));
};

void Scene::SetPointers()
{
	entity_pointers.clear();
    entity_pointers.emplace_back(player);
	for (auto& animated_entity : animated_entities)
	{
		entity_pointers.emplace_back(&animated_entity);
	}
};

std::vector<BufferQueueElement>& Scene::GetBufferQueue()
{
	return buffer_queue;
}

Frame& Scene::GetColorData()
{
	return terrain.GetColorData();
};

std::vector<vector2i>& Scene::GetShadowData()
{
    return terrain.GetShadowData();
}

void Scene::AddEntityAnimated(const EntityAnimated &entityAnimated)
{
    animated_entities.emplace_back(entityAnimated);
};

void Scene::UpdateBufferQueue()
{
	buffer_queue.clear();
	vector2i position;
	vector2i offset;
	for (auto& entity_pointer : entity_pointers)
	{
		position = entity_pointer->GetPosition();
		offset = entity_pointer->animator.GetAnimationOffset();
		BufferQueueElement temporary_buffer_queue_element(entity_pointer->animator.GetCurrentFrameObject(), { position.x + offset.x,position.y + offset.y }, position.y);
		buffer_queue.emplace_back(temporary_buffer_queue_element);
	}
};

void Scene::UpdateMovement()
{
	vector2i entity_position = { 0,0 };
	vector2i entity_move_direction = { 0,0 };

	Frame terrain_hitbox_data = terrain.GetHitboxData();
	vector2i terrain_size = terrain.GetSize();

	int colision_check_distance = 5;

	int from_x = 0;
	int to_x = 0;
	int from_y = 0;
	int to_y = 0;

	for (auto& entity_pointer : entity_pointers)
	{
		entity_move_direction = entity_pointer->GetMoveDirection();
		if (entity_move_direction.x == 0 && entity_move_direction.y == 0) continue;

		entity_position = entity_pointer->GetPosition();
		entity_move_direction = entity_pointer->GetMoveDirection();
		from_x = entity_position.x - colision_check_distance;
		from_y = entity_position.y - colision_check_distance;
		to_x = entity_position.x + colision_check_distance;
		to_y = entity_position.y + colision_check_distance;

		entity_pointer->SetPosition({ entity_position.x + entity_move_direction.x, entity_position.y + entity_move_direction.y });
		bool entity_can_move = true;

		for (int y = from_y; y < to_y && entity_can_move; y++)
		{
			for (int x = from_x; x < to_x && entity_can_move; x++)
			{
				if (x >= 0 && x < terrain_size.x && y >= 0 && y < terrain_size.y)
				{
					if (terrain_hitbox_data.Read(x, y) == 1)
					{
						for (int i = 0; i < entity_pointer->GetHitboxCount() && entity_can_move; i++)
						{
							if (!entity_pointer->GetHitboxActive(i) || entity_pointer->GetHitboxCinematic(i)) continue;

							if (entity_pointer->HitboxIntersect(i, { x,y }))
							{
								entity_can_move = false;
							}
						}
					}
				}
			}
		}
		for (auto& entity_pointer2 : entity_pointers)
		{
			if (!entity_can_move) break;
			if (entity_pointer->GetID() == entity_pointer2->GetID()) continue;

			for (int i = 0; i < entity_pointer->GetHitboxCount() && entity_can_move; i++)
			{
				if (!entity_pointer->GetHitboxActive(i))continue;
				for (int i2 = 0; i2 < entity_pointer2->GetHitboxCount() && entity_can_move; i2++)
				{
					if (!entity_pointer2->GetHitboxActive(i2) || entity_pointer2->GetHitboxCinematic(i2))continue;

					if (entity_pointer->HitboxIntersect(i, entity_pointer2->GetHitboxOffset(i2)))
					{
						entity_can_move = false;
					}
				}
			}
		}
		if (entity_can_move)
		{
			entity_pointer->SetNextMoveTime();
		}
		else
		{
			entity_pointer->SetPosition({ entity_position.x, entity_position.y});
		}
	}
};

void Scene::UpdateEntities()
{
	for (auto& entity_pointer : entity_pointers)
	{
		entity_pointer->Update();
	}
}

void Scene::Update()
{
	SetPointers();
	UpdateMovement();
	UpdateEntities();
	UpdateBufferQueue();
};

