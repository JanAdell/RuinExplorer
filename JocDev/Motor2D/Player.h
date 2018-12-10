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
	virtual bool Load(pugi::xml_node &node);
	virtual	bool Save(pugi::xml_node &node) const;
	bool CleanUp();


public:
	//Mix_Chunk* player_death = nullptr;
	//SDL_Texture * player_tex = nullptr;
	//SDL_Texture* teleport_tex = nullptr;
	iPoint position;
	iPoint respawnPlayer;
	int normal_jump;
	int boosted_jump;
	int distance_to_jump;
	float gravity;
	bool start_jump = false;
	bool stay_in_platform = false;
	bool top_jump = true;
	bool attack = false;
	fPoint speed;

private:
	Animation* current_animation = nullptr;
	Animation teleport;
	Animation idle;
	Animation run;
	Animation jump_anim;
	Animation fall;
	//int pos_collidery;
	iPoint player_size;
	uint sfx;

};

#endif
