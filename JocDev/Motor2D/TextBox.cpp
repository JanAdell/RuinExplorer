#include "p2Defs.h"
#include "Textbox.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1GUI.h"
#include "GUI.h"

Textbox::Textbox(const iPoint position, const p2SString text, _TTF_Font* font, SDL_Color color) : j1GUI{}
{

	this->font = font;
	SetText(text);

}

Textbox::~Textbox()
{
}

void Textbox::SetText(p2SString text)
{
	text.create(text.GetString());
	App->font->CalcSize(text.GetString(), element.w, element.h, font);
	element.x = element.y = 0;
	text_draw = App->font->Print(text.GetString(), color, font);
}

bool Textbox::Draw()
{
	App->render->Blit(text_draw, position.x - element.w, position.y - element.h, flip, &(animation->GetCurrentFrame()));

	return false;
}