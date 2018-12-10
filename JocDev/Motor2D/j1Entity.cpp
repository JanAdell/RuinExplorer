#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Entity.h"
#include "j1Textures.h"
#include "Entity.h"
#include "j1Audio.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "p2Log.h"
#include "j1Collisions.h"
#include "Brofiler/Brofiler.h"


#define SPAWN_MARGIN 2000
#define SCREEN_SIZE 1

j1Entity::j1Entity()
{
	name.create("Entity");
	for (uint i = 0; i < MAX_ENTITIES; ++i)
		entities[i] = nullptr;
}

// Destructor
j1Entity::~j1Entity()
{
}

bool j1Entity::Start()
{

	sprites = App->tex->Load("../Game/maps/enemy.png");
	return true;
}

bool j1Entity::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateEntity", Profiler::Color::Pink);
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEntity(queue[i]);
				queue[i].type = ENTITY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return true;
}

// Called before render is available
bool j1Entity::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntity", Profiler::Color::LightPink);

	for (uint i = 0; i < MAX_ENTITIES; ++i)
		if (entities[i] != nullptr)
			entities[i]->Update(dt);

	for (uint i = 0; i < MAX_ENTITIES; ++i)
		if (entities[i] != nullptr) 
			entities[i]->Draw(sprites);

	return true;
}

bool j1Entity::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateEntity", Profiler::Color::HotPink);

	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (-entities[i]->position.y * SCREEN_SIZE < (App->render->camera.y - App->render->camera.h) - SPAWN_MARGIN)
			{
				delete entities[i];
				entities[i] = nullptr;
			}
		}
	}

	return true;
}

// Called before quitting
bool j1Entity::CleanUp()
{
	LOG("Freeing all enemies");

	App->tex->UnLoad(sprites);

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}


	return true;
}

bool j1Entity::AddEntity(ENTITY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type == ENTITY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

bool j1Entity::Load(pugi::xml_node & data)
{
	for (uint i = 0; i < MAX_ENTITIES; i++)
	{
		if (entities[i] != nullptr)
		{
			if (queue[i].type == ENTITY_TYPES::ENTITY_EYEMONSTER)
			{
				pugi::xml_node eyemonster_data = data.child("eyemonster");
				entities[i]->Load(eyemonster_data);
			}
			if (queue[i].type == ENTITY_TYPES::ENTITY_BOAR)
			{
				pugi::xml_node boar_data = data.child("boar");
				entities[i]->Load(boar_data);
			}
			if (queue[i].type == ENTITY_TYPES::ENTITY_PLAYER)
			{
				pugi::xml_node player_data = data.child("player");
				entities[i]->Load(player_data);
			}
		}
	}
	return true;
}

bool j1Entity::Save(pugi::xml_node & data) const
{
	for (uint i = 0; i < MAX_ENTITIES; i++)
	{
		if (entities[i] != nullptr)
		{
			if ( queue[i].type == ENTITY_TYPES::ENTITY_EYEMONSTER)
			{
				pugi::xml_node eyemonster_data = data.append_child("eyemonster");
				entities[i]->Save(eyemonster_data);
			}
			if (queue[i].type == ENTITY_TYPES::ENTITY_BOAR)
			{
				pugi::xml_node boar_data = data.append_child("boar");
				entities[i]->Save(boar_data);
			}
			if (queue[i].type == ENTITY_TYPES::ENTITY_PLAYER)
			{
				pugi::xml_node player_data = data.append_child("player");
				entities[i]->Save(player_data);
			}
		}
	}
	return true;
}

void j1Entity::SpawnEntity(const EntityInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_ENTITIES; ++i);
	switch (info.type)
	{
	case ENTITY_TYPES::ENTITY_PLAYER:
		entities[i] = new Player(info.x, info.y);
		break;
	case ENTITY_TYPES::ENTITY_EYEMONSTER:
		entities[i] = new EyeMonster(info.x, info.y);
		break;
	case ENTITY_TYPES::ENTITY_BOAR:
		entities[i] = new boar(info.x, info.y);
		break;
	}
	
}

void j1Entity::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->GetCollider() == c1)
		{
			entities[i]->OnCollision(c2);
			if (c2->type == COLLIDER_PLAYER)
			{		
				delete entities[i];
				entities[i] = nullptr;
			}
		}

	}
}