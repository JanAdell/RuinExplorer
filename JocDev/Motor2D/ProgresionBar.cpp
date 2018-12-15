#include "ProgresionBar.h"

ProgresionBar::ProgresionBar(int x , int y): Sprites(x,y)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node progresNode = file.child("GUI").child("Sprites");

		progresbar_anim.PushBack({ progresNode.child("progresbar_anim").attribute("x1").as_int(), progresNode.child("progresbar_anim").attribute("y1").as_int(), progresNode.child("progresbar_anim").attribute("w1").as_int(), progresNode.child("progresbar_anim").attribute("h1").as_int() });
		progresbar_anim.speed = progresNode.child("progresbar_anim").attribute("speed").as_float();
		progresbar_anim.loop = false;

		animation = &progresbar_anim;
	}
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

ProgresionBar::~ProgresionBar()
{
}

void ProgresionBar::Update(float dt)
{
	animation = &progresbar_anim;
}

