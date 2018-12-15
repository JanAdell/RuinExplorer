#include "lifes.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1GUI.h"
#include "j1Entity.h"

Lifes::Lifes(int x, int y) : Sprites(x, y)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node lifeNode = file.child("GUI").child("Sprites");

		//3 life in 1 anim
		life_anim.PushBack({ lifeNode.child("lifes_anim").attribute("x1").as_int(), lifeNode.child("lifes_anim").attribute("y1").as_int(), lifeNode.child("lifes_anim").attribute("w1").as_int(), lifeNode.child("lifes_anim").attribute("h1").as_int() });
		life_anim.PushBack({ lifeNode.child("lifes_anim").attribute("x2").as_int(), lifeNode.child("lifes_anim").attribute("y2").as_int(), lifeNode.child("lifes_anim").attribute("w2").as_int(), lifeNode.child("lifes_anim").attribute("h2").as_int() });
		life_anim.PushBack({ lifeNode.child("lifes_anim").attribute("x3").as_int(), lifeNode.child("lifes_anim").attribute("y3").as_int(), lifeNode.child("lifes_anim").attribute("w3").as_int(), lifeNode.child("lifes_anim").attribute("h3").as_int() });
		life_anim.speed = lifeNode.child("lifes_anim").attribute("speed").as_float();
		life_anim.loop = false;

		max_life = lifeNode.child("health").attribute("max_life").as_int();
		min_life = lifeNode.child("health").attribute("min_life").as_int();
	}
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

Lifes::~Lifes()
{
}

void Lifes::Update(float dt)
{
	animation = &life_anim;
	if (App->entities->player != nullptr)
	{
		if (App->entities->player->lifes == max_life)
		{
			life_anim.current_frame = 2;
		}
		if (App->entities->player->lifes == min_life)
		{
			life_anim.current_frame = 1;
		}
		else
		{
			life_anim.current_frame = 0;
		}
	}
}


