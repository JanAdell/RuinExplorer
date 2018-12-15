#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "Player.h"
#include "j1Audio.h"
#include "j1Map.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Entity.h"
#include "j1Collisions.h"
#include "j1FadetoBlack.h"
#include "j1Pathfinding.h"
#include "p2Log.h"
#include "j1Scene.h"
#include <stdio.h>



Player::Player(int x, int y):Entity(x,y)
{
	pugi::xml_parse_result result = file.load_file("Entities.xml");

	if (result != NULL)
	{
		pugi::xml_node node = file.child("entities");

		speed.x = node.child("player").child("speed").attribute("x").as_float();
		speed.y = node.child("player").child("speed").attribute("y").as_float();

		player_size.x = node.child("player").child("idle_anim").attribute("w1").as_int();
		player_size.y = node.child("player").child("idle_anim").attribute("h1").as_int();

		gravity = node.child("player").child("speed").attribute("gravity").as_float();
		normal_jump = node.child("player").child("jump").attribute("normal").as_float();
		boosted_jump = node.child("player").child("jump").attribute("boost").as_float();

		hit = node.child("player").child("hit").attribute("x").as_int();
		lifes = node.child("player").child("health").attribute("life").as_int();

		pugi::xml_node anim = node.child("player");

		idle.PushBack({ anim.child("idle_anim").attribute("x1").as_int(),anim.child("idle_anim").attribute("y1").as_int(),anim.child("idle_anim").attribute("w1").as_int(),anim.child("idle_anim").attribute("h1").as_int() });
		idle.PushBack({ anim.child("idle_anim").attribute("x2").as_int(),anim.child("idle_anim").attribute("y2").as_int(),anim.child("idle_anim").attribute("w2").as_int(),anim.child("idle_anim").attribute("h2").as_int() });
		idle.PushBack({ anim.child("idle_anim").attribute("x3").as_int(),anim.child("idle_anim").attribute("y3").as_int(),anim.child("idle_anim").attribute("w3").as_int(),anim.child("idle_anim").attribute("h3").as_int() });
		idle.PushBack({ anim.child("idle_anim").attribute("x4").as_int(),anim.child("idle_anim").attribute("y4").as_int(),anim.child("idle_anim").attribute("w4").as_int(),anim.child("idle_anim").attribute("h4").as_int() });
		idle.loop = true;
		idle.speed = anim.child("idle_anim").attribute("speed").as_float();

		run.PushBack({ anim.child("run_anim").attribute("x1").as_int(),anim.child("run_anim").attribute("y1").as_int(),anim.child("run_anim").attribute("w1").as_int(),anim.child("run_anim").attribute("h1").as_int() });
		run.PushBack({ anim.child("run_anim").attribute("x2").as_int(),anim.child("run_anim").attribute("y2").as_int(),anim.child("run_anim").attribute("w2").as_int(),anim.child("run_anim").attribute("h2").as_int() });
		run.PushBack({ anim.child("run_anim").attribute("x3").as_int(),anim.child("run_anim").attribute("y3").as_int(),anim.child("run_anim").attribute("w3").as_int(),anim.child("run_anim").attribute("h3").as_int() });
		run.PushBack({ anim.child("run_anim").attribute("x4").as_int(),anim.child("run_anim").attribute("y4").as_int(),anim.child("run_anim").attribute("w4").as_int(),anim.child("run_anim").attribute("h4").as_int() });
		run.PushBack({ anim.child("run_anim").attribute("x5").as_int(),anim.child("run_anim").attribute("y5").as_int(),anim.child("run_anim").attribute("w5").as_int(),anim.child("run_anim").attribute("h5").as_int() });
		run.PushBack({ anim.child("run_anim").attribute("x6").as_int(),anim.child("run_anim").attribute("y6").as_int(),anim.child("run_anim").attribute("w6").as_int(),anim.child("run_anim").attribute("h6").as_int() });
		run.loop = true;
		run.speed = anim.child("run_anim").attribute("speed").as_float();

		jump_anim.PushBack({ anim.child("jump_anim").attribute("x1").as_int(),anim.child("jump_anim").attribute("y1").as_int(),anim.child("jump_anim").attribute("w1").as_int(),anim.child("jump_anim").attribute("h1").as_int() });
		jump_anim.PushBack({ anim.child("jump_anim").attribute("x2").as_int(),anim.child("jump_anim").attribute("y2").as_int(),anim.child("jump_anim").attribute("w2").as_int(),anim.child("jump_anim").attribute("h2").as_int() });
		jump_anim.loop = false;
		jump_anim.speed = anim.child("jump_anim").attribute("speed").as_float();

		//fall
		fall.PushBack({ anim.child("fall_anim").attribute("x1").as_int(),anim.child("fall_anim").attribute("y1").as_int(),anim.child("fall_anim").attribute("w1").as_int(),anim.child("fall_anim").attribute("h1").as_int() });
		fall.PushBack({ anim.child("fall_anim").attribute("x2").as_int(),anim.child("fall_anim").attribute("y2").as_int(),anim.child("fall_anim").attribute("w2").as_int(),anim.child("fall_anim").attribute("h2").as_int() });
		fall.loop = false;
		fall.speed = anim.child("fall_anim").attribute("speed").as_float();

		Attack.PushBack({ anim.child("attack_anim").attribute("x1").as_int(),anim.child("attack_anim").attribute("y1").as_int(),anim.child("attack_anim").attribute("w1").as_int(),anim.child("attack_anim").attribute("h1").as_int() });
		Attack.PushBack({ anim.child("attack_anim").attribute("x2").as_int(),anim.child("attack_anim").attribute("y2").as_int(),anim.child("attack_anim").attribute("w2").as_int(),anim.child("attack_anim").attribute("h2").as_int() });
		Attack.PushBack({ anim.child("attack_anim").attribute("x3").as_int(),anim.child("attack_anim").attribute("y3").as_int(),anim.child("attack_anim").attribute("w3").as_int(),anim.child("attack_anim").attribute("h3").as_int() });
		Attack.loop = false;
		Attack.speed = anim.child("attack_anim").attribute("speed").as_float();

		collider = App->collisions->AddCollider({ position.x,position.y,player_size.x,player_size.y - 5 }, COLLIDER_PLAYER, (j1Module*)App->entities);
		
		top_jump = true;

		tpsfx = App->audio->LoadFx("audio/fx/Randomize3.wav");
		deathsfx = App->audio->LoadFx("audio/fx/Death.wav");
	}
}

Player::~Player()
{
	LOG("Unloading player");
	App->audio->UnloadFx(tpsfx);
	App->audio->UnloadFx(deathsfx);
}

// Update: draw background
void Player::Update(float dt)
{

	//pos_collidery = position.y + 30;
	animation = &idle;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		animation = &run;
		entityflip = SDL_RendererFlip::SDL_FLIP_NONE;
		position.x += speed.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		animation = &run;
		entityflip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		position.x -= speed.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		top_jump = true;
		attack = true;
	}
	//jump
	if (stay_in_platform)
	{
		attack = false;
		Attack.Reset();
		fall.Reset();
		jump_anim.Reset();
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
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
			animation = &jump_anim;
			position.y -= speed.y + gravity;
		}
		if (position.y == distance_to_jump)
			top_jump = true;
		if (top_jump == true)
		{
			if (attack == true)
			{
				position.y += gravity;
				animation = &Attack;
			}
			else
				animation = &fall;
			
		}
	}
	position.y += gravity;
	stay_in_platform = false;

	//tp mechanic
	if (App->scene->volcan_map)
	{

		if (position.x > App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width)
		{
			teleport.Reset();
			App->audio->PlayFx(tpsfx);
			position.x = 7 * App->map->data.tile_width;
		}

		else if (position.x < 7 * App->map->data.tile_width)
		{
			teleport.Reset();
			position.x = App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width;
			App->audio->PlayFx(tpsfx);
		}
	}
	else
	{
		if (position.x > App->map->data.tile_width * App->map->data.width - 8 * App->map->data.tile_width)
		{
			teleport.Reset();
			App->audio->PlayFx(tpsfx);
			position.x = 8 * App->map->data.tile_width;
			animation = &teleport;
		}

		else if (position.x < 8 * App->map->data.tile_width)
		{
			teleport.Reset();
			position.x = App->map->data.tile_width * App->map->data.width - 8 * App->map->data.tile_width;
			App->audio->PlayFx(tpsfx);
			animation = &teleport;
		}
	}

	//damage moviment
	if (recivedamageL)
	{
		if (damageM > position.x)
		{
			position.x += speed.y;
		}
		else
			recivedamageL = false;
	}
	if (recivedamageR)
	{
		if (damageM < position.x)
		{
			position.x -= speed.y;
		}
		else
			recivedamageR = false;
	}

}

void Player::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_WALL)
	{
		if (position.y + player_size.y < collider->rect.y + 10)
		{
			stay_in_platform = true;
			position.y -= gravity;
		}
		else
		{
			if (position.x > collider->rect.x + collider->rect.w - 10)
				position.x += speed.x;

			if (position.x + player_size.x < collider->rect.x + 10)
				position.x -= speed.x;
		}
		if (position.y > collider->rect.y + collider->rect.h - 10)
			top_jump = true;
		
	}
	if (collider->type == COLLIDER_BOOST)
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

	if (collider->type == COLLIDER_ENEMY)
	{
		if (position.y + player_size.y > collider->rect.y - 10 && !attack)
		{
			App->audio->PlayFx(deathsfx);
			--lifes;
			if (lifes <= 0) 
			{
				App->scene->death();
			}
			else
			{
				if (position.x > collider->rect.x + collider->rect.w - 10)
				{
					recivedamageL = true;
					damageM = position.x + hit;
				}

				if (position.x + player_size.x < collider->rect.x + 10)
				{
					recivedamageR = true;
					damageM = position.x - hit;
				}
			}
		}
	}

	if (collider->type == COLLIDER_FINISH)
	{
		//win condition

		App->map->CleanUp();
		App->entities->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack();

		if (App->scene->volcan_map)
		{	
			if (App->map->Load("SeaTempleMap.tmx"))
			{
				int w, h;
				uchar* data = NULL;
				if (App->map->CreateWalkabilityMap(w, h, &data))
					App->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);

			}
			App->audio->PlayMusic("audio/music/AncientRuins.ogg", DEFAULT_MUSIC_FADE_TIME);
			App->scene->volcan_map = false;
		}
		else if (!App->scene->volcan_map)
		{
			if (App->map->Load("Volcano_Map.tmx"))
			{
				int w, h;
				uchar* data = NULL;
				if (App->map->CreateWalkabilityMap(w, h, &data))
					App->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);

			}
			App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
			App->scene->volcan_map = true;

		}
		App->render->Start();
		App->entities->Start();
		App->collisions->Start();
	}

}


bool Player::Load(pugi::xml_node& data)
{
	position.x = data.child("player").attribute("x").as_int();
	position.y = data.child("player").attribute("y").as_int();

	return true;
}

// Save Game State
bool Player::Save(pugi::xml_node& data) const
{
	pugi::xml_node pos = data.append_child("player");

	pos.append_attribute("x") = position.x;
	pos.append_attribute("y") = position.y;

	return true;
}

