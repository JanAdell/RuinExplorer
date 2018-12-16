#include "Bar.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1GUI.h"
#include "j1Input.h"


bar::bar(int x, int y):Sprites(x,y,GUI_TYPES::BAR)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node barNode = file.child("GUI").child("Sprites");

		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x0").as_int(), barNode.child("bar_anim").attribute("y0").as_int(), barNode.child("bar_anim").attribute("w0").as_int(), barNode.child("bar_anim").attribute("h0").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x1").as_int(), barNode.child("bar_anim").attribute("y1").as_int(), barNode.child("bar_anim").attribute("w1").as_int(), barNode.child("bar_anim").attribute("h1").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x2").as_int(), barNode.child("bar_anim").attribute("y2").as_int(), barNode.child("bar_anim").attribute("w2").as_int(), barNode.child("bar_anim").attribute("h2").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x2").as_int(), barNode.child("bar_anim").attribute("y2").as_int(), barNode.child("bar_anim").attribute("w2").as_int(), barNode.child("bar_anim").attribute("h2").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x3").as_int(), barNode.child("bar_anim").attribute("y3").as_int(), barNode.child("bar_anim").attribute("w3").as_int(), barNode.child("bar_anim").attribute("h3").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x4").as_int(), barNode.child("bar_anim").attribute("y4").as_int(), barNode.child("bar_anim").attribute("w4").as_int(), barNode.child("bar_anim").attribute("h4").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x5").as_int(), barNode.child("bar_anim").attribute("y5").as_int(), barNode.child("bar_anim").attribute("w5").as_int(), barNode.child("bar_anim").attribute("h5").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x6").as_int(), barNode.child("bar_anim").attribute("y6").as_int(), barNode.child("bar_anim").attribute("w6").as_int(), barNode.child("bar_anim").attribute("h6").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x7").as_int(), barNode.child("bar_anim").attribute("y7").as_int(), barNode.child("bar_anim").attribute("w7").as_int(), barNode.child("bar_anim").attribute("h7").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x8").as_int(), barNode.child("bar_anim").attribute("y8").as_int(), barNode.child("bar_anim").attribute("w8").as_int(), barNode.child("bar_anim").attribute("h8").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x9").as_int(), barNode.child("bar_anim").attribute("y9").as_int(), barNode.child("bar_anim").attribute("w9").as_int(), barNode.child("bar_anim").attribute("h9").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x10").as_int(), barNode.child("bar_anim").attribute("y10").as_int(), barNode.child("bar_anim").attribute("w10").as_int(), barNode.child("bar_anim").attribute("h10").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x11").as_int(), barNode.child("bar_anim").attribute("y11").as_int(), barNode.child("bar_anim").attribute("w11").as_int(), barNode.child("bar_anim").attribute("h11").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x12").as_int(), barNode.child("bar_anim").attribute("y12").as_int(), barNode.child("bar_anim").attribute("w12").as_int(), barNode.child("bar_anim").attribute("h12").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x13").as_int(), barNode.child("bar_anim").attribute("y13").as_int(), barNode.child("bar_anim").attribute("w13").as_int(), barNode.child("bar_anim").attribute("h13").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x14").as_int(), barNode.child("bar_anim").attribute("y14").as_int(), barNode.child("bar_anim").attribute("w14").as_int(), barNode.child("bar_anim").attribute("h14").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x14").as_int(), barNode.child("bar_anim").attribute("y14").as_int(), barNode.child("bar_anim").attribute("w14").as_int(), barNode.child("bar_anim").attribute("h14").as_int() });
		bar_anim.PushBack({ barNode.child("bar_anim").attribute("x14").as_int(), barNode.child("bar_anim").attribute("y14").as_int(), barNode.child("bar_anim").attribute("w14").as_int(), barNode.child("bar_anim").attribute("h14").as_int() });
		bar_anim.speed = barNode.child("bar_anim").attribute("speed").as_float();
		bar_anim.loop = false;
		prevframe = bar_anim.current_frame;
	}
	flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
	barpos = position;
}

bar::~bar()
{
}

void bar::Update(float dt)
{
	if (App->render->start)
	{
		animation = &bar_anim;
		if (bar_anim.current_frame < 16)
		{	
			if (prevframe != bar_anim.GetCurrentFrameIndex())
			{
				prevframe = bar_anim.current_frame;
				position.y -= 14;
			}
		}
	}
	else
	{
		bar_anim.Reset();
		position.y = barpos.y + 14;
	}
	
	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		saveframe = bar_anim.current_frame;

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		bar_anim.current_frame = saveframe;

}
