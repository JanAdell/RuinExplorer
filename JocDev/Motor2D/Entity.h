#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "Animation.h"
#include "j1Audio.h"


struct SDL_Texture;
struct Collider;

class Entity 
{
protected:
	Animation * animation = nullptr;
	Collider* collider = nullptr;

public:
	iPoint position;

public:
	Entity(int x, int y);
	virtual ~Entity();

	const Collider* GetCollider() const;
	uint points = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);

};

#endif // __ENEMY_H__
