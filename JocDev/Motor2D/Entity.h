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
	pugi::xml_document file;
public:
	Entity(int x, int y);
	virtual ~Entity();

	const Collider* GetCollider() const;
	uint points = 0;
	bool stay_in_platform = false;

	virtual void Update(float dt) = 0;
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider) = 0;
	virtual bool Load(pugi::xml_node &node) { return true; };
	virtual	bool Save(pugi::xml_node &node) const { return true; };

};

#endif 
