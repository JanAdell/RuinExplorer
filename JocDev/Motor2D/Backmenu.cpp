#include "Backmenu.h"
#include "j1GUI.h"
#include "j1App.h"

backmenu::backmenu(int x, int y) :Sprites(x, y, GUI_TYPES::BACKMENU)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node backNode = file.child("GUI").child("Sprites");

		open.PushBack({ backNode.child("backmenu_open").attribute("x1").as_int(), backNode.child("backmenu_open").attribute("y1").as_int(), backNode.child("backmenu_open").attribute("w1").as_int(), backNode.child("backmenu_open").attribute("h1").as_int() });
		open.PushBack({ backNode.child("backmenu_open").attribute("x2").as_int(), backNode.child("backmenu_open").attribute("y2").as_int(), backNode.child("backmenu_open").attribute("w2").as_int(), backNode.child("backmenu_open").attribute("h2").as_int() });
		open.PushBack({ backNode.child("backmenu_open").attribute("x2").as_int(), backNode.child("backmenu_open").attribute("y2").as_int(), backNode.child("backmenu_open").attribute("w2").as_int(), backNode.child("backmenu_open").attribute("h2").as_int() });
		open.PushBack({ backNode.child("backmenu_open").attribute("x3").as_int(), backNode.child("backmenu_open").attribute("y3").as_int(), backNode.child("backmenu_open").attribute("w3").as_int(), backNode.child("backmenu_open").attribute("h3").as_int() });
		open.PushBack({ backNode.child("backmenu_open").attribute("x4").as_int(), backNode.child("backmenu_open").attribute("y4").as_int(), backNode.child("backmenu_open").attribute("w4").as_int(), backNode.child("backmenu_open").attribute("h4").as_int() });
		open.PushBack({ backNode.child("backmenu_open").attribute("x5").as_int(), backNode.child("backmenu_open").attribute("y5").as_int(), backNode.child("backmenu_open").attribute("w5").as_int(), backNode.child("backmenu_open").attribute("h5").as_int() });
		open.speed = backNode.child("backmenu_open").attribute("speed").as_float();
		open.loop = false;

		close.PushBack({ backNode.child("backmenu_close").attribute("x1").as_int(), backNode.child("backmenu_close").attribute("y1").as_int(), backNode.child("backmenu_close").attribute("w1").as_int(), backNode.child("backmenu_close").attribute("h1").as_int() });
		close.PushBack({ backNode.child("backmenu_close").attribute("x2").as_int(), backNode.child("backmenu_close").attribute("y2").as_int(), backNode.child("backmenu_close").attribute("w2").as_int(), backNode.child("backmenu_close").attribute("h2").as_int() });
		close.PushBack({ backNode.child("backmenu_close").attribute("x2").as_int(), backNode.child("backmenu_close").attribute("y2").as_int(), backNode.child("backmenu_close").attribute("w2").as_int(), backNode.child("backmenu_close").attribute("h2").as_int() });
		close.PushBack({ backNode.child("backmenu_close").attribute("x3").as_int(), backNode.child("backmenu_close").attribute("y3").as_int(), backNode.child("backmenu_close").attribute("w3").as_int(), backNode.child("backmenu_close").attribute("h3").as_int() });
		close.PushBack({ backNode.child("backmenu_close").attribute("x4").as_int(), backNode.child("backmenu_close").attribute("y4").as_int(), backNode.child("backmenu_close").attribute("w4").as_int(), backNode.child("backmenu_close").attribute("h4").as_int() });
		close.PushBack({ backNode.child("backmenu_close").attribute("x5").as_int(), backNode.child("backmenu_close").attribute("y5").as_int(), backNode.child("backmenu_close").attribute("w5").as_int(), backNode.child("backmenu_close").attribute("h5").as_int() });
		close.speed = backNode.child("backmenu_open").attribute("speed").as_float();
		close.loop = false;

		idle.PushBack({ backNode.child("backmenu_idle").attribute("x1").as_int(), backNode.child("backmenu_idle").attribute("y1").as_int(), backNode.child("backmenu_idle").attribute("w1").as_int(), backNode.child("backmenu_idle").attribute("h1").as_int() });
		idle.speed = backNode.child("backmenu_idle").attribute("speed").as_float();
		idle.loop = false;


	}
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

backmenu::~backmenu()
{
}

void backmenu::Update(float dt)
{
	if (close.current_frame >= 5)
		animation = &open;
	for (int i = 0; i < MAX_GUI; ++i)
	{
		if (App->gui->gui[i] != nullptr)
		{
			if (App->gui->gui[i]->type == GUI_TYPES::BUTTON)
			{
				if (App->gui->gui[i]->GetPush() == true)
				{
					close.Reset();
					animation = &close;
					closed = true;
				}
			}
		}
	}

	if (closed == false)
	{
		animation = &idle;
	}

	if (animation == &open)
		saveframe = open.current_frame;
	else
		saveframe = close.current_frame;

}
