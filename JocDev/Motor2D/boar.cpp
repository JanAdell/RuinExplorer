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
	pugi::xml_parse_result result = file.load_file("Entities.xml");

	if (result != NULL)
	{
		pugi::xml_node node = file.child("entities");

		speed.x = node.child("boar").child("speed").attribute("x").as_float();
		speed.y = node.child("boar").child("speed").attribute("y").as_float();

		next_ground = node.child("boar").child("objective").attribute("x").as_float();
		
		search = node.child("boar").child("search").attribute("x").as_int();

		pugi::xml_node anim = node.child("boar").child("anim");

		boaranim.PushBack({ anim.attribute("x1").as_int(), anim.attribute("y1").as_int(), anim.attribute("w1").as_int(), anim.attribute("h1").as_int() });
		boaranim.PushBack({ anim.attribute("x2").as_int(), anim.attribute("y2").as_int(), anim.attribute("w2").as_int(), anim.attribute("h2").as_int() });
		boaranim.PushBack({ anim.attribute("x3").as_int(), anim.attribute("y3").as_int(), anim.attribute("w3").as_int(), anim.attribute("h3").as_int() });
		boaranim.PushBack({ anim.attribute("x4").as_int(), anim.attribute("y4").as_int(), anim.attribute("w4").as_int(), anim.attribute("h4").as_int() });
		boaranim.loop = true;
		boaranim.speed = anim.attribute("speed").as_float();
		animation = &boaranim;

		collider = App->collisions->AddCollider({ position.x, position.y, anim.attribute("w3").as_int(), anim.attribute("h3").as_int() }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->entities);
	}
}
void boar::Update(float dt)
{

	enemy_pos = App->map->WorldToMap(position.x, position.y);
	player_pos = App->map->WorldToMap(App->entities->player->position.x, App->entities->player->position.y);
	ground.x = enemy_pos.x;
	ground.y = enemy_pos.y + speed.y;
	if (App->pathfinding->IsWalkable(ground))
	{
		position.y += speed.y;
	}
		
	if (enemy_pos.DistanceManhattan(player_pos) < search)
	{
		enemypath = App->pathfinding->GetLastPath();
		if (App->pathfinding->CreatePath(enemy_pos, player_pos,ENTITY_BOAR) != -1)
		{
			if (App->collisions->debug)
			{
				for (uint i = 0; i < enemypath->Count(); i++)
				{
					iPoint road = App->map->MapToWorld(enemypath->At(i)->x, enemypath->At(i)->y);
					App->render->DrawQuad({ road.x ,road.y ,App->map->data.tile_width,App->map->data.tile_height }, 100, 0, 100, 80);
				}
			}
			
			if (position != App->entities->player->position)
			{
				if (enemypath->Count() > 0)
				{
					objective = iPoint(enemypath->At(0)->x, enemypath->At(0)->y);
		
					
					if (objective.x <= enemy_pos.x )
					{
						left = true;

					}
					else if (objective.x > enemy_pos.x)
					{
						left = false;
					}					
				}
			}
		}
		if (left)
		{
			position.x -= speed.x;
			entityflip = SDL_FLIP_HORIZONTAL;

		}

		else
		{
			position.x += speed.x;
			entityflip = SDL_FLIP_NONE;
	
		}
	}
	else
	{

		if (left)
		{
			ground = { enemy_pos.x - next_ground, enemy_pos.y + next_ground };
			if (!App->pathfinding->IsWalkable(ground))
			{
				position.x -= speed.x;
				entityflip = SDL_FLIP_HORIZONTAL;
			}
			else
				left = false;
		}

		else
		{
			ground = { enemy_pos.x + next_ground, enemy_pos.y + next_ground };
			if (!App->pathfinding->IsWalkable(ground))
			{
				position.x += speed.x;
				entityflip = SDL_FLIP_NONE;
			}

			else
				left = true;
		}
	}


}


void boar::OnCollision(Collider* collider)
{

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