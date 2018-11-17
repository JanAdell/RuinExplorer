#include "j1App.h"
#include "Entity.h"
#include "j1Collisions.h"
#include "j1Render.h"
#include "j1Entity.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "Brofiler/Brofiler.h"

Entity::Entity(int x, int y) : position(x, y)
{
}

Entity::~Entity()
{
	if (collider != nullptr)
		collider->to_delete = true;
	collider = nullptr;
}

const Collider* Entity::GetCollider() const
{
	return collider;
}

void Entity::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, App->entities->enemyflip ,&(animation->GetCurrentFrame()));
}

void Entity::OnCollision(Collider * collider)
{
	if (collider == App->player->collider_player)
	{
		App->scene->death();
	}
}