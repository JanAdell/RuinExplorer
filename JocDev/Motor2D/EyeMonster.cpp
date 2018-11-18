#include "j1App.h"
#include "EyeMonster.h"
#include "j1Collisions.h"
#include "j1Player.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Entity.h"
#include "j1Pathfinding.h"
#include "j1Map.h"


EyeMonster::EyeMonster(int x, int y) : Entity(x, y)
{
	eyemonster.PushBack({ 51, 88, 25, 30 });
	eyemonster.PushBack({ 108, 91, 26, 27 });
	eyemonster.PushBack({ 165, 92, 27, 26 });
	eyemonster.PushBack({ 225, 92, 20, 26 });
	eyemonster.loop = true;
	eyemonster.speed = 0.1f;
	animation = &eyemonster;
	collider = App->collisions->AddCollider({ position.x, position.y, 26, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->entities);
}
void EyeMonster::Update(float dt)
{
	enemy_pos = App->map->WorldToMap(position.x, position.y);
	player_pos = App->map->WorldToMap(App->player->position.x,App->player->position.y);

	if (enemy_pos.DistanceManhattan(player_pos) < 10)
	{
		if (App->pathfinding->CreatePath(enemy_pos, player_pos, ENTITY_EYEMONSTER) != -1)
		{
			enemypath = App->pathfinding->GetLastPath();
			if (App->collisions->debug)
			{
				for (uint i = 0; i < enemypath->Count(); i++)
				{
					iPoint road = App->map->MapToWorld(enemypath->At(i)->x, enemypath->At(i)->y);
					App->render->DrawQuad({ road.x ,road.y ,App->map->data.tile_width,App->map->data.tile_height }, 100, 100, 0, 80);
				}
			}
			if (position != App->player->position)
			{
				if (enemypath->Count() > 0)
				{
					objective = iPoint(enemypath->At(0)->x, enemypath->At(0)->y);
					if (objective.x <= enemy_pos.x)
					{
						left = true;

					}
					else if (objective.x > enemy_pos.x)
					{
						left = false;
					}
					if (objective.y <= enemy_pos.y)
					{
						position.y += -1;
					}
					else if (objective.y > enemy_pos.y)
					{
						position.y += 1;
					}
				}
			}
		}
	}
	else
	{
		if (position.x == 8 * App->map->data.tile_width)
		{
			left = false;
		}
		if (position.x == App->map->data.tile_width * App->map->data.width - 8 * App->map->data.tile_width)
		{
			left = true;
		}

	}
	if (left)
	{
		position.x -= 1;
		App->entities->enemyflip = SDL_FLIP_NONE;
	}

	else
	{
		position.x += 1;
		App->entities->enemyflip = SDL_FLIP_HORIZONTAL;
	}
}


void EyeMonster::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER)
	{
		App->scene->death();
		
	}
	if (collider->type == COLLIDER_WALL)
		left = !left;
}

bool EyeMonster::Load(pugi::xml_node & data)
{

	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}

bool EyeMonster::Save(pugi::xml_node & data) const
{
	pugi::xml_node pos = data.append_child("position");

	pos.append_attribute("x") = position.x;
	pos.append_attribute("y") = position.y;

	return true;
}

bool EyeMonster::CleanUp()
{
	
	return true;
}