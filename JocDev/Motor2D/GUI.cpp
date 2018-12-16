#include "GUI.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1GUI.h"


GUI::GUI(int x, int y, GUI_TYPES type, GUI_TYPES subtype) : position(x, y), type(type), subtype(subtype)
{
}

GUI::~GUI()
{

}

const iPoint GUI::GetPos() const
{
	return position;
}



void GUI::Draw(SDL_Texture * sprites,float dt)
{
	if (animation != nullptr)
	{
		if (type == GUI_TYPES::COLLECTIVE)
		{
			App->render->Blit(sprites, position.x, position.y, flip, &(animation->GetCurrentFrame(dt)));
		}
		if (type == GUI_TYPES::BUTTON || type == GUI_TYPES::SPRITES)
		{
			App->render->Blit(sprites, position.x, position.y, flip, &(animation->GetCurrentFrame(dt)),0.0f);
		}
		if (type == GUI_TYPES::TEXTBOX)
		{
			App->render->Blit(text_draw, position.x, position.y, flip, NULL, 0.0f);

		}
	}
}

bool GUI::Load(pugi::xml_node & node)
{
	position.x = node.child("position").attribute("x").as_int();
	position.x = node.child("position").attribute("y").as_int();
	if (subtype == GUI_TYPES::BAR)
	{
		saveframe = node.child("frame").attribute("frame").as_float();
	}
	else if (subtype == GUI_TYPES::COIN)
	{
		colcoin = node.child("collect").attribute("collect").as_bool();
	}
	return true;
}

bool GUI::Save(pugi::xml_node & node) const
{
	pugi::xml_node pos = node.append_child("position");

	pos.append_attribute("x") = position.x;
	pos.append_attribute("y") = position.y;

	if (subtype == GUI_TYPES::BAR)
	{
		pugi::xml_node frame = node.append_child("frame");

		frame.append_attribute("frame") = saveframe;
	}

	else if (subtype == GUI_TYPES::COIN)
	{
		pugi::xml_node col = node.append_child("collect");

		col.append_attribute("collect") = colcoin;
	}
	return true;
}
