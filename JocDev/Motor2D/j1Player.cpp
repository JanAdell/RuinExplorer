#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "p2Log.h"
#include <stdio.h>



j1Player::j1Player()
{
	name.create("player");

	// idle animation
}

j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node & conf)
{
	bool ret = true;
	position.x = conf.child("position").attribute("x").as_int();
	position.y = conf.child("position").attribute("y").as_int();
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

	//if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	//{
	//	if (turbo == false)
	//	{
	//		position.x += (speed * 2);
	//	}
	//	else
	//	{
	//		position.x += 3;
	//	}
	//}


	//if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	//{
	//	if (turbo == false)
	//	{
	//		position.y -= (speed * 2);
	//	}
	//	else
	//	{
	//		position.y -= 3;
	//	}


	//	if (current_animation != &up)
	//	{
	//		up.Reset();
	//		current_animation = &up;
	//	}


	//}

	//if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	//{
	//	if (turbo == false)
	//	{
	//		position.y += (speed * 2);

	//	}
	//	else
	//	{
	//		position.y += 3;
	//	}

	//	if (current_animation != &down)
	//	{
	//		down.Reset();
	//		current_animation = &down;
	//	}

	//}
	//if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	//{
	//	if (turbo == false)
	//	{
	//		position.x -= (speed * 2);
	//	}
	//	else
	//	{
	//		position.x -= 3;
	//	}

	//}


	//if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->controller[BUTTON_A] == KEY_STATE::KEY_DOWN)
	//{
	//	if (wave == false)
	//	{
	//		App->particles->AddParticle(App->particles->explosion_shot, position.x + 37, position.y + 1);
	//		App->particles->AddParticle(App->particles->laser, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT);
	//		App->audio->PlaySoundEffect(shot_particle);
	//	}
	//	if (cd < 5)
	//	{
	//		cd++;
	//	}
	//	else
	//	{

	//		if (bomb)
	//		{
	//			App->particles->AddParticle(App->particles->bombPU, position.x, position.y + 7, COLLIDER_PLAYER_SHOT);
	//		}
	//		cd = 0;
	//	}
	//}

	//if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	//	&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
	//	current_animation = &idle;

	//if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	//{

	//	App->fade->FadeToBlack((Module*)App->background, (Module*)App->win_lose);
	//	App->background->win = false;

	//}
	//if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	//{
	//	App->fade->FadeToBlack((Module*)App->background, (Module*)App->win_lose);
	//	App->background->win = true;
	//}
	////powerup
	//if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN)
	//{
	//	tentacles = !tentacles;
	//	if (App->tentacle->IsEnabled())
	//		App->tentacle->Disable();
	//	else App->tentacle->Enable();
	//}
	//if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN)
	//{
	//	bomb = !bomb;
	//}
	//if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN)
	//{
	//	turbo = !turbo;
	//	App->particles->boost = true;
	//}
	App->render->Blit(player_tex, position.x, position.y, &sprite_player);

	return true;
}

//void j1Player::OnCollision(Collider* c1, Collider* c2)
//{
//	if (c1 == col && destroyed == false && App->fade->IsFading() == false)
//	{
//	}
//}
