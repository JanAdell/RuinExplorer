#include "Sliderbar.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1GUI.h"
#include "j1Audio.h"


sliderbar::sliderbar(int x, int y):GUI(x,y,GUI_TYPES::SLIDER, GUI_TYPES::NO_TYPES)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node Node = file.child("GUI").child("slider");

		anim.PushBack({ Node.child("anim").attribute("x1").as_int(), Node.child("anim").attribute("y1").as_int(), Node.child("anim").attribute("w1").as_int(), Node.child("anim").attribute("h1").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x2").as_int(), Node.child("anim").attribute("y2").as_int(), Node.child("anim").attribute("w2").as_int(), Node.child("anim").attribute("h2").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x3").as_int(), Node.child("anim").attribute("y3").as_int(), Node.child("anim").attribute("w3").as_int(), Node.child("anim").attribute("h3").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x4").as_int(), Node.child("anim").attribute("y4").as_int(), Node.child("anim").attribute("w4").as_int(), Node.child("anim").attribute("h4").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x5").as_int(), Node.child("anim").attribute("y5").as_int(), Node.child("anim").attribute("w5").as_int(), Node.child("anim").attribute("h5").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x6").as_int(), Node.child("anim").attribute("y6").as_int(), Node.child("anim").attribute("w6").as_int(), Node.child("anim").attribute("h6").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x7").as_int(), Node.child("anim").attribute("y7").as_int(), Node.child("anim").attribute("w7").as_int(), Node.child("anim").attribute("h7").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x8").as_int(), Node.child("anim").attribute("y8").as_int(), Node.child("anim").attribute("w8").as_int(), Node.child("anim").attribute("h8").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x9").as_int(), Node.child("anim").attribute("y9").as_int(), Node.child("anim").attribute("w9").as_int(), Node.child("anim").attribute("h9").as_int() });
		anim.PushBack({ Node.child("anim").attribute("x10").as_int(), Node.child("anim").attribute("y10").as_int(), Node.child("anim").attribute("w10").as_int(), Node.child("anim").attribute("h10").as_int() });
		anim.speed = Node.child("anim").attribute("speed").as_float();
		anim.loop = false;

		size.x = Node.child("anim").attribute("w1").as_int();
		size.y = Node.child("anim").attribute("h1").as_int();
		pich = Node.child("volume").attribute("value").as_float();
	}
	flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
}

sliderbar::~sliderbar()
{
}

void sliderbar::Update(float dt)
{
	animation = &anim;
	App->input->GetMousePosition(mousepos.x, mousepos.y);

	if (position.x < mousepos.x && position.x + size.x > mousepos.x
		&& position.y < mousepos.y && position.y + size.y > mousepos.y )
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			pich =(float)(mousepos.x - position.x) / size.x ;
		}
	}
	anim.current_frame = pich * 10;
	Mix_VolumeMusic(pich*128);
}

bool sliderbar::GetPush()
{
	return false;
}
