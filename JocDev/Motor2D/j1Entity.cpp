#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Entity.h"
#include "j1Textures.h"
#include "Entity.h"
#include "j1Audio.h"
#include "j1Player.h"
#include "p2Log.h"

#define SPAWN_MARGIN 2000
#define SCREEN_SIZE 1

j1Entity::j1Entity()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		entities[i] = nullptr;
}

// Destructor
j1Entity::~j1Entity()
{
}

bool j1Entity::Start()
{
	bool lets = false;
	bool letb = false;
	bool lett = false;

	sprites = App->tex->Load("Sprites_Assets/all_enemies.png");
	return true;
}

bool j1Entity::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{
			if (queue[i].y * SCREEN_SIZE < App->render->camera.y - (App->render->camera.h * SCREEN_SIZE) - SPAWN_MARGIN)
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
bool j1Entity::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (entities[i] != nullptr)
			entities[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (entities[i] != nullptr) entities[i]->Draw(sprites);

	return true;
}

bool j1Entity::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->position.y * SCREEN_SIZE > (App->render->camera.y + App->render->camera.h) + SPAWN_MARGIN)
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

	for (uint i = 0; i < MAX_ENEMIES; ++i)
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

	for (uint i = 0; i < MAX_ENEMIES; ++i)
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

void j1Entity::SpawnEntity(const EntityInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENTITY_TYPES::PLAYER:
			/*entities[i] = new playerEntity(info.x, info.y);
			queue[i].enemy_life = 5;*/
			break;
		}
	}
}

void j1Entity::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->GetCollider() == c1)
		{

			if (queue[i].enemy_life <= 0)
			{
				entities[i]->OnCollision(c2);
				delete entities[i];
				entities[i] = nullptr;
			}
		}

	}
}