#ifndef _TEXT_BOX_
#define _TEXT_BOX_

#include "GUI.h"
#include "p2Point.h"
#include "SDL_ttf/include/SDL_ttf.h"


class Textbox : public GUI
{
public:

	Textbox(const iPoint position, const p2SString text, _TTF_Font* font, const SDL_Color color);
	
	~Textbox();

	void SetText(p2SString text);
	void Update(float dt);
	void Draw();

	bool GetPush();

private:
	_TTF_Font*			font = nullptr;
	SDL_Color           color = { 255,255,255,255 };
	p2SString		    text;
	Animation * animation = nullptr;
	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
	SDL_Rect element;
	SDL_Texture* text_draw;

};


#endif 
