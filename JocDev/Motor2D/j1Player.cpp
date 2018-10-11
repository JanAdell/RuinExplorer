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
	return ret;
}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	player_tex = App->tex->Load("maps/adventurer.png"); 
	sprite_player = {266,46,20,27 };

	position.y = App->map->data.tile_height * App->map->data.height - 3 * App->map->data.tile_height + App->map->data.tile_height/2;
	position.x = App->map->data.tile_width * App->map->data.width / 2;
	normal_jump = App->map->data.tile_height * 4;
	boosted_jump = App->map->data.tile_height * 8;
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

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speed.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (boost_jump == false && start_jump == false)
		{
			distance_to_jump = position.y - normal_jump;
			start_jump = true;
		}
	}

	if (start_jump)
	{
		if (distance_to_jump < position.y)
			position.y -= speed.y;
		else
		{
			start_jump = false;
		}
	}

	if (position.x > App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width)
		position.x = 7 * App->map->data.tile_width;

	else if (position.x < 7 * App->map->data.tile_width)
		position.x = App->map->data.tile_width * App->map->data.width - 7 * App->map->data.tile_width;
	App->render->Blit(player_tex, position.x, position.y, &sprite_player);

	return true;
}

//void j1Player::OnCollision(Collider* c1, Collider* c2)
//{
//	if (c1 == col && destroyed == false && App->fade->IsFading() == false)
//	{
//	}
//}
