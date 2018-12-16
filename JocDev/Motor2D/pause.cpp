#include "Pause.h"
#include "j1GUI.h"

Pause::Pause(int x, int y):Sprites(x,y,GUI_TYPES::PAUSE)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node pauseNode = file.child("GUI").child("Sprites");
		pause_anim.PushBack({ pauseNode.child("pause_anim").attribute("x5").as_int(), pauseNode.child("pause_anim").attribute("y5").as_int(), pauseNode.child("pause_anim").attribute("w5").as_int(), pauseNode.child("pause_anim").attribute("h5").as_int() });
		pause_anim.speed = pauseNode.child("pause_anim").attribute("speed").as_float();
		pause_anim.loop = false;

	}
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
	pause_anim.current_frame = 1;
}

Pause::~Pause()
{
}

void Pause::Update(float dt)
{
	pause_anim.current_frame = 1;
	animation = &pause_anim;
}
