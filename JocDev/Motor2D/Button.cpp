#include "Button.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1GUI.h"

Button::Button(int x, int y, GUI_TYPES subtype, p2SString txt) : GUI(x, y,GUI_TYPES::BUTTON,subtype)
{
	pugi::xml_parse_result result = file.load_file("GUI.xml");
	if (result != NULL)
	{
		pugi::xml_node buttonNode = file.child("GUI").child("button");

		buttonsize.x = buttonNode.child("idle_anim").attribute("w1").as_int();
		buttonsize.y = buttonNode.child("idle_anim").attribute("h1").as_int();

		idle.PushBack({ buttonNode.child("idle_anim").attribute("x1").as_int(), buttonNode.child("idle_anim").attribute("y1").as_int(), buttonNode.child("idle_anim").attribute("w1").as_int(), buttonNode.child("idle_anim").attribute("h1").as_int() });
		idle.speed = buttonNode.child("idle_anim").attribute("speed").as_float();
		idle.loop = false;

		select.PushBack({ buttonNode.child("select_anim").attribute("x1").as_int(), buttonNode.child("select_anim").attribute("y1").as_int(), buttonNode.child("select_anim").attribute("w1").as_int(), buttonNode.child("select_anim").attribute("h1").as_int() });
		select.speed = buttonNode.child("select_anim").attribute("speed").as_float();
		select.loop = false;

		push.PushBack({ buttonNode.child("push_anim").attribute("x1").as_int(), buttonNode.child("push_anim").attribute("y1").as_int(), buttonNode.child("push_anim").attribute("w1").as_int(), buttonNode.child("push_anim").attribute("h1").as_int() });
		push.speed = buttonNode.child("push_anim").attribute("speed").as_float();
		push.loop = false;
		flip = SDL_RendererFlip::SDL_FLIP_NONE;
	}
	App->gui->AddGui(x, y, GUI_TYPES::TEXTBOX, GUI_TYPES::NO_TYPES, txt);
	clickfx = App->audio->LoadFx("audio/fx/click1.wav");
}

Button::~Button()
{
	App->audio->UnloadFx(clickfx);
}

void Button::Update(float dt)
{
	iPoint mousePos;
	App->input->GetMousePosition(mousePos.x, mousePos.y);
	if (mousePos.x > position.x && mousePos.x < position.x + buttonsize.x
		&& mousePos.y> position.y && mousePos.y < position.y + buttonsize.y)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			active = false;
			animation = &push;
			App->audio->PlayFx(clickfx);
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
			active = true;
		else
		{
			animation = &select;
			active = false;
		}
	}
	else
	{
		animation = &idle;
		active = false;
	}
}

bool Button::GetPush()
{
	return active;
}

