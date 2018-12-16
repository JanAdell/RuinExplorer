#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "Animation.h"
#include "j1Audio.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )


struct SDL_Texture;
struct Collider;

class Entity 
{
protected:
	Animation * animation = nullptr;
	Collider* collider = nullptr;
	SDL_RendererFlip entityflip;
public:
	iPoint position;
	pugi::xml_document file;
public:
	Entity(int x, int y);
	~Entity();

	const Collider* GetCollider() const;
	uint points = 0;
	bool stay_in_platform = false;
	int lifes;
	virtual void Update(float dt) = 0;
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider) = 0;
	virtual bool Load(pugi::xml_node &node) = 0;
	virtual	bool Save(pugi::xml_node &node)const = 0;

};

#endif 
