#ifndef __j1Entity_H__
#define __j1Entity_H__

#include "j1Module.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#include "EyeMonster.h"
#include "boar.h"

#define MAX_ENTITIES 100

enum ENTITY_TYPES
{
	NO_TYPE,
	ENTITY_PLAYER,
	ENTITY_EYEMONSTER,
	ENTITY_BOAR
};

class Entity;

struct EntityInfo
{
	ENTITY_TYPES type = ENTITY_TYPES::NO_TYPE;
	int x, y;
};

class j1Entity : public j1Module
{
public:

	j1Entity();
	~j1Entity();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEntity(ENTITY_TYPES type, int x, int y);
	bool Load(pugi::xml_node &data);
	bool Save(pugi::xml_node &data) const;
	SDL_RendererFlip enemyflip;

	EntityInfo queue[MAX_ENTITIES];
	Entity* entities[MAX_ENTITIES];
	ENTITY_TYPES type = ENTITY_TYPES::NO_TYPE;

private:

	void SpawnEntity(const EntityInfo& info);

public:

	SDL_Texture * sprites;
};
#endif