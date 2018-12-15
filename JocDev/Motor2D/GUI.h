#ifndef _GUI_H_
#define _GUI_H_


#include "p2Point.h"
#include "Animation.h"
#include "j1Audio.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )


struct SDL_Texture;
enum GUI_TYPES;
class GUI
{
public:
	GUI(int x, int y, GUI_TYPES type);
	~GUI();

	const iPoint GetPos() const;

	virtual void Update(float dt) = 0;
	void Draw(SDL_Texture* sprites);
protected:
	Animation * animation = nullptr;
	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
public:
	iPoint position;
	pugi::xml_document file;
	GUI_TYPES type;
	bool gui_delete = false;

};

#endif