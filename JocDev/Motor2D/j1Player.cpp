#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Map.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Collisions.h"
#include "p2Log.h"
#include "j1Scene.h"
#include <stdio.h>



j1Player::j1Player()
{
	name.create("player");
}

j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node & conf)
{
	bool ret = true;
	speed.x = conf.child("speed").attribute("x").as_float();
	speed.y = conf.child("speed").attribute("y").as_float();
	player_size.x =	conf.child("idle_anim").attribute("w1").as_int();
	player_size.y = conf.child("idle_anim").attribute("h1").as_int();
	gravity = conf.child("speed").attribute("gravity").as_float();
	//sprites
	//idle
	idle.PushBack({ conf.child("idle_anim").attribute("x1").as_int(),conf.child("idle_anim").attribute("y1").as_int(),conf.child("idle_anim").attribute("w1").as_int(),conf.child("idle_anim").attribute("h1").as_int() });
	idle.PushBack({ conf.child("idle_anim").attribute("x2").as_int(),conf.child("idle_anim").attribute("y2").as_int(),conf.child("idle_anim").attribute("w2").as_int(),conf.child("idle_anim").attribute("h2").as_int() });
	idle.PushBack({ conf.child("idle_anim").attribute("x3").as_int(),conf.child("idle_anim").attribute("y3").as_int(),conf.child("idle_anim").attribute("w3").as_int(),conf.child("idle_anim").attribute("h3").as_int() });
	idle.PushBack({ conf.child("idle_anim").attribute("x4").as_int(),conf.child("idle_anim").attribute("y4").as_int(),conf.child("idle_anim").attribute("w4").as_int(),conf.child("idle_anim").attribute("h4").as_int() });
	idle.loop = true;
	idle.speed = 0.05f;

	//run
	run.PushBack({ conf.child("run_anim").attribute("x1").as_int(),conf.child("run_anim").attribute("y1").as_int(),conf.child("run_anim").attribute("w1").as_int(),conf.child("run_anim").attribute("h1").as_int() });
	run.PushBack({ conf.child("run_anim").attribute("x2").as_int(),conf.child("run_anim").attribute("y2").as_int(),conf.child("run_anim").attribute("w2").as_int(),conf.child("run_anim").attribute("h2").as_int() });
	run.PushBack({ conf.child("run_anim").attribute("x3").as_int(),conf.child("run_anim").attribute("y3").as_int(),conf.child("run_anim").attribute("w3").as_int(),conf.child("run_anim").attribute("h3").as_int() });
	run.PushBack({ conf.child("run_anim").attribute("x4").as_int(),conf.child("run_anim").attribute("y4").as_int(),conf.child("run_anim").attribute("w4").as_int(),conf.child("run_anim").attribute("h4").as_int() });
	run.PushBack({ conf.child("run_anim").attribute("x5").as_int(),conf.child("run_anim").attribute("y5").as_int(),conf.child("run_anim").attribute("w5").as_int(),conf.child("run_anim").attribute("h5").as_int() });
	run.PushBack({ conf.child("run_anim").attribute("x6").as_int(),conf.child("run_anim").attribute("y6").as_int(),conf.child("run_anim").attribute("w6").as_int(),conf.child("run_anim").attribute("h6").as_int() });
	run.loop = true;
	run.speed = 0.2;

	//jump
	jump_anim.PushBack({ conf.child("jump_anim").attribute("x1").as_int(),conf.child("jump_anim").attribute("y1").as_int(),conf.child("jump_anim").attribute("w1").as_int(),conf.child("jump_anim").attribute("h1").as_int() });
	jump_anim.PushBack({ conf.child("jump_anim").attribute("x2").as_int(),conf.child("jump_anim").attribute("y2").as_int(),conf.child("jump_anim").attribute("w2").as_int(),conf.child("jump_anim").attribute("h2").as_int() });
	jump_anim.loop = false;
	jump_anim.speed = 0.1;

	//fall
	fall.PushBack({ conf.child("fall_anim").attribute("x1").as_int(),conf.child("fall_anim").attribute("y1").as_int(),conf.child("fall_anim").attribute("w1").as_int(),conf.child("fall_anim").attribute("h1").as_int() });
	fall.PushBack({ conf.child("fall_anim").attribute("x2").as_int(),conf.child("fall_anim").attribute("y2").as_int(),conf.child("fall_anim").attribute("w2").as_int(),conf.child("fall_anim").attribute("h2").as_int() });
	fall.loop = false;
	fall.speed = 0.1;


	return ret;
}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	player_tex = App->tex->Load("adventurer/adventurer.png"); 
	position.y = respawnPlayer.y;
	position.x = respawnPlayer.x;
	normal_jump = App->map->data.tile_height * 4;
	boosted_jump = App->map->data.tile_height * 8;
	top_jump = true;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;

	collider_player_down = App->collisions->AddCollider({ position.x + 2, position.y + player_size.y, player_size.x - 2, 1 }, COLLIDER_PLAYER_DOWN, this);
	collider_player_up = App->collisions->AddCollider({ position.x + 2,position.y - 3,player_size.x - 2,1 }, COLLIDER_PLAYER_UP,this);
	collider_player_left = App->collisions->AddCollider({ position.x,position.y,2,player_size.y - 3 }, COLLIDER_PLAYER_LEFT,this);
	collider_player_right = App->collisions->AddCollider({ position.x + player_size.x,position.y,2,player_size.y - 3 }, COLLIDER_PLAYER_RIGHT,this);
	collider_player = App->collisions->AddCollider({ position.x,position.y,player_size.x,player_size.y}, COLLIDER_PLAYER, this);

	cameralimit = App->collisions->AddCollider({ App->render->camera.x, -App->render->camera.y,App->render->camera.w, 2}, COLLIDER_LIMIT_CAMERA, this);

	App->audio->LoadFx("audio/fx/Teleport.wav");
	App->audio->LoadFx("audio/fx/Death.wav");

	return ret;
}


bool j1Player::CleanUp()
{
	LOG("Unloading player");
	App->audio->UnloadFx(1);
	//App->audio->UnloadFx(2);
	App->tex->UnLoad(player_tex);
	player_tex = nullptr;
	return true;

}


// Update: draw background
bool j1Player::Update(float dt)
{
	pos_collidery = position.y + 30;
	current_animation = &idle;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		current_animation = &run;
		flip = SDL_RendererFlip :: SDL_FLIP_NONE;
		position.x += speed.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		current_animation = &run;
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		position.x -= speed.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		top_jump = true;
	}
	//jump
	if (stay_in_platform)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			start_jump = false;
			if (start_jump == false)
			{
				jump_anim.Reset();
				distance_to_jump = position.y - normal_jump;
				position.y -= speed.y + gravity;
				start_jump = true;
				stay_in_platform = false;
				top_jump = false;
			}
		}
	}
	else
	{
		if (position.y > distance_to_jump && top_jump == false)
		{
			current_animation = &jump_anim;
			position.y -= speed.y + gravity;
		}
		if (position.y == distance_to_jump)
			top_jump = true;
		if(top_jump == true)
		{
			current_animation = &fall;
		}
	}
	position.y += gravity;
	stay_in_platform = false;

	//mechanic
	if (App->scene->volcan_map)
	{

		if (position.x > App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width)
		{
			App->audio->PlayFx(2, 0);
			position.x = 7 * App->map->data.tile_width;
		}

		else if (position.x < 7 * App->map->data.tile_width)
		{
			position.x = App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width;	
			App->audio->PlayFx(2, 0);
		}
	}
	else
	{
		if (position.x > App->map->data.tile_width * App->map->data.width - 8 * App->map->data.tile_width)
		{
			position.x = 8 * App->map->data.tile_width;
		}

		else if (position.x < 8 * App->map->data.tile_width)
		{
			position.x = App->map->data.tile_width * App->map->data.width - 8 * App->map->data.tile_width;
			App->audio->PlayFx(2, 0);
		}
	}

	//colliders player
	collider_player_down->SetPos(position.x + 2, position.y + player_size.y);
	collider_player_up->SetPos(position.x + 2, position.y - 3);
	collider_player_left->SetPos(position.x, position.y);
	collider_player_right->SetPos(position.x + player_size.x, position.y);
	collider_player->SetPos(position.x, position.y);

	cameralimit->SetPos(App->render->camera.x, -App->render->camera.y);
	App->render->Blit(player_tex, position.x, position.y,flip, &(current_animation->GetCurrentFrame()));


	return true;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER_LEFT && c2->type == COLLIDER_WALL)
	{
		position.x += speed.x;
	}
	else if (c1->type == COLLIDER_PLAYER_RIGHT && c2->type == COLLIDER_WALL)
	{
		position.x -= speed.x;
	}
	else if (c1->type == COLLIDER_PLAYER_DOWN && c2->type == COLLIDER_WALL)
	{
		position.y -= gravity;
		stay_in_platform = true;
	}
	else if (c1->type == COLLIDER_PLAYER_UP && c2->type == COLLIDER_WALL)
	{
		top_jump = true;
	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_BOOST)
	{
		if (stay_in_platform == true && App->input->GetKey(SDL_SCANCODE_SPACE))
		{
			start_jump = false;
			jump_anim.Reset();
			distance_to_jump = position.y - boosted_jump;
			position.y -= speed.y;
			start_jump = true;
			stay_in_platform = false;
			top_jump = false;
		}
	}
	if (c1->type == COLLIDER_PLAYER_UP && c2->type == COLLIDER_LIMIT_CAMERA)
	{
		position.y += gravity;
	}

}


bool j1Player::Load(pugi::xml_node& data)
{
	position.x = data.child("player").attribute("x").as_int();
	position.y = data.child("player").attribute("y").as_int();

	return true;
}

// Save Game State
bool j1Player::Save(pugi::xml_node& data) const
{
	pugi::xml_node pos = data.append_child("player");

	pos.append_attribute("x") = position.x;
	pos.append_attribute("y") = position.y;

	return true;
}