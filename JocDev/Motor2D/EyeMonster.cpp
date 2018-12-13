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
	pugi::xml_parse_result result = file.load_file("Entities.xml");
	
	if (result != NULL)
	{
		pugi::xml_node node = file.child("entities");

		speed.x = node.child("eyemonster").child("speed").attribute("x").as_float();
		speed.y = node.child("eyemonster").child("speed").attribute("y").as_float();

		search = node.child("eyemonster").child("search").attribute("x").as_int();

		pugi::xml_node anim = node.child("eyemonster").child("anim");
		monstersize = anim.attribute("w1").as_int() - 10;
		eyemonster.PushBack({ anim.attribute("x1").as_int(), anim.attribute("y1").as_int(), anim.attribute("w1").as_int(), anim.attribute("h1").as_int() });
		eyemonster.PushBack({ anim.attribute("x2").as_int(), anim.attribute("y2").as_int(), anim.attribute("w2").as_int(), anim.attribute("h2").as_int() });
		eyemonster.PushBack({ anim.attribute("x3").as_int(), anim.attribute("y3").as_int(), anim.attribute("w3").as_int(), anim.attribute("h3").as_int() });
		eyemonster.PushBack({ anim.attribute("x4").as_int(), anim.attribute("y4").as_int(), anim.attribute("w4").as_int(), anim.attribute("h4").as_int() });
		eyemonster.loop = true;
		eyemonster.speed = anim.attribute("speed").as_float();
		animation = &eyemonster;

		collider = App->collisions->AddCollider({ position.x + 20, position.y + 20, anim.attribute("w3").as_int() - 10, anim.attribute("h3").as_int() -10}, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->entities);
	}
}
void EyeMonster::Update(float dt)
{
	enemy_pos = App->map->WorldToMap(position.x, position.y);
	player_pos = App->map->WorldToMap(App->entities->player->position.x, App->entities->player->position.y);

	if (enemy_pos.DistanceManhattan(player_pos) < search)
	{
		if (App->pathfinding->CreatePath(enemy_pos, player_pos, ENTITY_EYEMONSTER) != -1)
		{
			enemypath = App->pathfinding->GetLastPath();
			if (App->collisions->debug)
			{
				for (uint i = 0; i < enemypath->Count(); i++)
				{
					iPoint road = App->map->MapToWorld(enemypath->At(i)->x, enemypath->At(i)->y);
					App->render->DrawQuad({ road.x ,road.y ,App->map->data.tile_width,App->map->data.tile_height }, 100, 100, 0, alpha);
				}
			}
			if (position != App->entities->player->position)
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
						position.y += -speed.y;
					}
					else if (objective.y > enemy_pos.y)
					{
						position.y += speed.y;
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
		position.x -= speed.x;
		entityflip = SDL_FLIP_NONE;
	}

	else
	{
		position.x += speed.x;
		entityflip = SDL_FLIP_HORIZONTAL;
	}
}


void EyeMonster::OnCollision(Collider* collider)
{

	if (collider->type == COLLIDER_WALL)
		left = !left;
	if (collider->type == COLLIDER_PLAYER)
	{
		if (position.x + 20 > collider->rect.x + collider->rect.w - 10)
			position.x += speed.x * 3;

		if (position.x + 20 + monstersize < collider->rect.x + 10)
			position.x -= speed.x * 3;
	}
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
