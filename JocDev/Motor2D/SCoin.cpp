#include "SCoin.h"
#include "j1GUI.h"

Scoin::Scoin(int x, int y):Sprites(x,y, GUI_TYPES::SPRITECOIN)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node coinNode = file.child("GUI").child("Sprites");

		SCoin_anim.PushBack({ coinNode.child("Scoin_anim").attribute("x1").as_int(), coinNode.child("Scoin_anim").attribute("y1").as_int(), coinNode.child("Scoin_anim").attribute("w1").as_int(), coinNode.child("Scoin_anim").attribute("h1").as_int() });
		SCoin_anim.speed = coinNode.child("Scoin_anim").attribute("speed").as_float();
		SCoin_anim.loop = true;

	}
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

Scoin::~Scoin()
{
}

void Scoin::Update(float dt)
{
	animation = &SCoin_anim;
}
