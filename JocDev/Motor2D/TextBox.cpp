#include "p2Defs.h"
#include "Textbox.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1GUI.h"
#include "GUI.h"

Textbox::Textbox(const iPoint position, const p2SString text, _TTF_Font* font, SDL_Color color) : GUI(position.x,position.y, GUI_TYPES::TEXTBOX,GUI_TYPES::NO_TYPES), font(font),text(text),color(color)
{
	SetText(text);
}

Textbox::~Textbox()
{
}

void Textbox::SetText(p2SString txt)
{
	text.create(txt.GetString());
	App->font->CalcSize(text.GetString(), element.w, element.h, font);
	element.x = element.y = 0;
	App->tex->UnLoad(text_draw);
	text_draw = App->font->Print(text.GetString(), color, font);
}

void Textbox::Update(float dt)
{
	Draw();
}

void Textbox::Draw()
{
	App->render->Blit(text_draw, position.x, position.y, flip,NULL,0.0f);

}

bool Textbox::GetPush()
{
	return false;
}
