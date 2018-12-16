#include "Coins.h"
#include "j1App.h"
#include "j1Entity.h"
#include "j1Scene.h"
#include "j1GUI.h"
#include "j1Input.h"

Coins::Coins(int x, int y):Collective(x,y,GUI_TYPES::COIN)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node coinNode = file.child("GUI").child("Collective");

		coin_anim.PushBack({ coinNode.child("coin_anim").attribute("x1").as_int(), coinNode.child("coin_anim").attribute("y1").as_int(), coinNode.child("coin_anim").attribute("w1").as_int(), coinNode.child("coin_anim").attribute("h1").as_int() });
		coin_anim.PushBack({ coinNode.child("coin_anim").attribute("x2").as_int(), coinNode.child("coin_anim").attribute("y2").as_int(), coinNode.child("coin_anim").attribute("w2").as_int(), coinNode.child("coin_anim").attribute("h2").as_int() });
		coin_anim.PushBack({ coinNode.child("coin_anim").attribute("x2").as_int(), coinNode.child("coin_anim").attribute("y2").as_int(), coinNode.child("coin_anim").attribute("w2").as_int(), coinNode.child("coin_anim").attribute("h2").as_int() });
		coin_anim.PushBack({ coinNode.child("coin_anim").attribute("x3").as_int(), coinNode.child("coin_anim").attribute("y3").as_int(), coinNode.child("coin_anim").attribute("w3").as_int(), coinNode.child("coin_anim").attribute("h3").as_int() });
		coin_anim.PushBack({ coinNode.child("coin_anim").attribute("x4").as_int(), coinNode.child("coin_anim").attribute("y4").as_int(), coinNode.child("coin_anim").attribute("w4").as_int(), coinNode.child("coin_anim").attribute("h4").as_int() });
		coin_anim.PushBack({ coinNode.child("coin_anim").attribute("x5").as_int(), coinNode.child("coin_anim").attribute("y5").as_int(), coinNode.child("coin_anim").attribute("w5").as_int(), coinNode.child("coin_anim").attribute("h5").as_int() });
		coin_anim.speed = coinNode.child("coin_anim").attribute("speed").as_float();
		coin_anim.loop = true;

		size.x = coinNode.child("coin_anim").attribute("w1").as_int();
		size.y = coinNode.child("coin_anim").attribute("h1").as_int();
	}
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
	coinsfx = App->audio->LoadFx("audio/fx/coin1.wav");
}

Coins::~Coins()
{
	App->audio->UnloadFx(coinsfx);
}

void Coins::Update(float dt)
{
	if (!collectcoin)
		animation = &coin_anim;
	else
		animation = nullptr;
	if (App->entities->player != nullptr)
	{
		if (position.x < App->entities->player->position.x && position.x + size.x > App->entities->player->position.x
			&& position.y < App->entities->player->position.y && position.y + size.y > App->entities->player->position.y && !collectcoin)
		{
			collectcoin = true;
			App->audio->PlayFx(coinsfx);
			collect++;

		}
	}

	if (App->scene->die)
	{
		collectcoin = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		colcoin = collectcoin;

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		collectcoin = colcoin;
	
}
