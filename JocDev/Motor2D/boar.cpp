#include "j1App.h"
#include "boar.h"
#include "j1Collisions.h"
#include "j1Player.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Entity.h"
#include "j1Pathfinding.h"
#include "j1Map.h"


boar::boar(int x, int y) : Entity(x, y)
{
	boaranim.PushBack({ 25, 171, 31, 31 });
	boaranim.PushBack({ 95, 171, 35, 31 });
	boaranim.PushBack({ 164, 171, 39, 31 });
	boaranim.PushBack({ 236, 171, 34, 31 });
	boaranim.loop = true;
	boaranim.speed = 0.1f;
	animation = &boaranim;
	collider = App->collisions->AddCollider({ position.x, position.y, 34, 31 }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->entities);
}
void boar::Update(float dt)
{

	enemy_pos = App->map->WorldToMap(position.x, position.y);
	player_pos = App->map->WorldToMap(App->player->position.x, App->player->position.y);

	if (enemy_pos.DistanceManhattan(player_pos) < 8)
	{
		if (App->pathfinding->CreatePath(enemy_pos, player_pos) != -1)
		{
			enemypath = App->pathfinding->GetLastPath();
			if (position != App->player->position)
			{
				if (enemypath->Count() > 0)
				{
					objective = iPoint(enemypath->At(0)->x, enemypath->At(0)->y);

				}
			}
		}
	}
	else
	{
		if (position.x == 7 * App->map->data.tile_width)
		{
			left = false;
		}
		if (position.x == App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width)
		{
			left = true;
		}

	}
	if (left)
	{
		position.x -= 1;
		App->entities->enemyflip = SDL_FLIP_HORIZONTAL;
	}

	else
	{
		position.x += 1;
		App->entities->enemyflip = SDL_FLIP_NONE;
	}
}


void boar::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER)
	{
		App->scene->death();

	}
	if (collider->type == COLLIDER_WALL)
		left = !left;
}

bool boar::Load(pugi::xml_node & data)
{

	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}

bool boar::Save(pugi::xml_node & data) const
{
	pugi::xml_node pos = data.append_child("position");

	pos.append_attribute("x") = position.x;
	pos.append_attribute("y") = position.y;

	return true;
}

bool boar::CleanUp()
{

	return true;
}