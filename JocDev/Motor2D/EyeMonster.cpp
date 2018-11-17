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
	eyemonster.PushBack({ 64, 97, 47, 47 });
	eyemonster.PushBack({ 174, 103, 48, 41 });
	eyemonster.PushBack({ 284, 103, 49, 42 });
	eyemonster.PushBack({ 397, 103, 39, 41 });
	eyemonster.loop = true;
	eyemonster.speed = 0.1f;
	animation = &eyemonster;
	collider = App->collisions->AddCollider({ position.x, position.y, 49, 42 }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->entities);
}
void EyeMonster::Update(float dt)
{

	enemy_pos = App->map->WorldToMap(position.x, position.y);
	player_pos = App->map->WorldToMap(App->player->position.x,App->player->position.y);
	player_pos.x += 1;
	player_pos.y -= 1;
		if (App->pathfinding->CreatePath(enemy_pos, player_pos) != -1)
		{
			enemypath = App->pathfinding->GetLastPath();
			if (position != App->player->position)
			{
				if (enemypath->Count() > 0)
				{
						path_to_follow = iPoint(enemypath->At(0)->x, enemypath->At(0)->y);
						if (path_to_follow.x < enemy_pos.x)
						{
							position.x += -1;

						}
						else if (path_to_follow.x > enemy_pos.x)
						{
							position.x += 1;
						}
						if (path_to_follow.y < enemy_pos.y)
						{
							position.y += -1;
						}
						else if (path_to_follow.y > enemy_pos.y)
						{
							position.y += 1;
						}
				}
			}
		}
	}


void EyeMonster::OnCollision(Collider* collider)
{
	
}

bool EyeMonster::CleanUp()
{
	
	return true;
}