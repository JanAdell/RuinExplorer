#include "j1App.h"
#include "EyeMonster.h"
#include "j1Collisions.h"
#include "j1Player.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Entity.h"
#include "j1Pathfinding.h"


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
	if (!App->pathfinding->active)
	{
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
		if (position.x == App->render->camera.x)
			left = false;
		if (position.x == App->render->camera.x + App->render->camera.w)
			left = true;
	}
	else
	{
		
		if (App->pathfinding->CreatePath(position, App->player->position) != -1)
		{
			enemypath = App->pathfinding->GetLastPath();
			if (position != App->player->position)
			{
				for (uint i = 0; i <= enemypath->Count(); i++)
				{
					if (enemypath->At(i)->x == position.x)
					{
						if (enemypath->At(i)->y == position.y + 1)
						{
							position.y += 1;
						}
						else if (enemypath->At(i)->y == position.y - 1)
						{
							position.y -= 1;
						}
					}

					else if (enemypath->At(i)->x == position.x + 1)
					{
						if (enemypath->At(i)->y == position.y + 1)
						{
							position.x += 1;
							position.y += 1;
						}
						else if (enemypath->At(i)->y == position.y - 1)
						{
							position.x += 1;
							position.y -= 1;
						}
					}

					else if (enemypath->At(i)->y == position.y)
					{
						if (enemypath->At(i)->x == position.x + 1)
						{
							position.x += 1;
						}
						else if (enemypath->At(i)->x == position.x - 1)
						{
							position.x -= 1;
						}
					}

					else if (enemypath->At(i)->y == position.y + 1)
					{
						if (enemypath->At(i)->x == position.x + 1)
						{
							position.y += 1;
							position.x += 1;
						}
						else if (enemypath->At(i)->x == position.x - 1)
						{
							position.y += 1;
							position.x -= 1;
						}
					}
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