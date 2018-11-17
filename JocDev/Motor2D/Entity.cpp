#include "j1App.h"
#include "Entity.h"
#include "j1Collisions.h"
#include "j1Render.h"
#include "j1Entity.h"

Entity::Entity(int x, int y) : position(x, y)
{}

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
		App->render->Blit(sprites, position.x, position.y, SDL_FLIP_NONE ,&(animation->GetCurrentFrame()));
}
