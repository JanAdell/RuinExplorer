#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "p2Log.h"
#include "j1Map.h"
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
	run.speed = 0.05;

	//jump
	jump_anim.PushBack({ conf.child("jump_anim").attribute("x1").as_int(),conf.child("jump_anim").attribute("y1").as_int(),conf.child("jump_anim").attribute("w1").as_int(),conf.child("jump_anim").attribute("h1").as_int() });
	jump_anim.PushBack({ conf.child("jump_anim").attribute("x2").as_int(),conf.child("jump_anim").attribute("y2").as_int(),conf.child("jump_anim").attribute("w2").as_int(),conf.child("jump_anim").attribute("h2").as_int() });
	jump_anim.loop = false;
	jump_anim.speed = 0.02;

	//fall
	fall.PushBack({ conf.child("fall_anim").attribute("x1").as_int(),conf.child("fall_anim").attribute("y1").as_int(),conf.child("fall_anim").attribute("w1").as_int(),conf.child("fall_anim").attribute("h1").as_int() });
	fall.PushBack({ conf.child("fall_anim").attribute("x2").as_int(),conf.child("fall_anim").attribute("y2").as_int(),conf.child("fall_anim").attribute("w2").as_int(),conf.child("fall_anim").attribute("h2").as_int() });
	fall.loop = false;
	fall.speed = 0.02;

	return ret;
}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	player_tex = App->tex->Load("adventurer/adventurer.png"); 
	position.y = App->map->data.tile_height * App->map->data.height - 3 * App->map->data.tile_height + App->map->data.tile_height/2;
	position.x = App->map->data.tile_width * App->map->data.width / 2;
	normal_jump = App->map->data.tile_height * 4;
	boosted_jump = App->map->data.tile_height * 8;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
	return ret;
}


bool j1Player::CleanUp()
{
	LOG("Unloading player");
	App->tex->UnLoad(player_tex);
	player_tex = nullptr;
	return true;
}





// Update: draw background
bool j1Player::Update(float dt)
{
	current_animation = &idle;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		current_animation = &run;
		flip = SDL_RendererFlip :: SDL_FLIP_NONE;
		position.x += speed.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		current_animation = &run;
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		position.x -= speed.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (boost_jump == false && start_jump == false)
		{
			jump_anim.Reset();
			distance_to_jump = position.y - normal_jump;
			start_jump = true;
		}
	}

	if (start_jump)
	{
		if (distance_to_jump < position.y)
		{
			current_animation = &jump_anim;
			position.y -= speed.y;
		}
		else
		{
			start_jump = false;
		}
	}

	if (position.x > App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width)
		position.x = 7 * App->map->data.tile_width;

	else if (position.x < 7 * App->map->data.tile_width)
		position.x = App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width;

	App->render->Blit(player_tex, position.x, position.y,flip, &(current_animation->GetCurrentFrame()));

	return true;
}

//void j1Player::OnCollision(Collider* c1, Collider* c2)
//{
//	if (c1 == col && destroyed == false && App->fade->IsFading() == false)
//	{
//	}
//}
