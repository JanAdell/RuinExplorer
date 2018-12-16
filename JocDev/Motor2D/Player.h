#ifndef __j1Player_H__
#define __j1Player_H__

#include "Entity.h"
#include "p2Point.h"
#include "Animation.h"
#include "../Motor2D/SDL/include/SDL_render.h "
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;
struct Collider;

class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();

	void Update(float dt);
	void OnCollision(Collider* collider);
	bool Load(pugi::xml_node &node);
	bool Save(pugi::xml_node &node) const;

public:

	int normal_jump;
	int boosted_jump;
	int distance_to_jump;
	float gravity;
	bool start_jump = false;
	bool top_jump = true;
	bool attack = false;
	bool recivedamageL = false;
	bool recivedamageR = false;
	int damageM,hit;
	iPoint speed;

	uint tpsfx;
	uint deathsfx;

private:
	Animation teleport;
	Animation idle;
	Animation run;
	Animation jump_anim;
	Animation fall;
	Animation Attack;
	//int pos_collidery;
	iPoint player_size;
	uint sfx;
	bool leftwall = false;
	bool rightwall = false;

};

#endif
