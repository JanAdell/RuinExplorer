#include "Credits.h"
#include "j1GUI.h"

credits::credits(int x, int y):Sprites(x,y,GUI_TYPES::CREDITS)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node creditsNode = file.child("GUI").child("Sprites");

		credits_anim.PushBack({ creditsNode.child("credits").attribute("x1").as_int(), creditsNode.child("credits").attribute("y1").as_int(), creditsNode.child("credits").attribute("w1").as_int(), creditsNode.child("credits").attribute("h1").as_int() });
		credits_anim.speed = creditsNode.child("credits").attribute("speed").as_float();
		credits_anim.loop = false;

		
	}
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

credits::~credits()
{
}

void credits::Update(float dt)
{
	animation = &credits_anim;
}
