#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "Button.h"
#include "Sprites.h"
#include "lifes.h"
#include "ProgresionBar.h"
#include "Bar.h"
#include "Coins.h"

#define CURSOR_WIDTH 2
#define MAX_GUI 50
// TODO 1: Create your structure of classes

enum GUI_TYPES
{
	NO_TYPES,
	BUTTON,
	SPRITES,
	LIFES,
	PROGRESBAR,
	BAR,
	COLLECTIVE,
	COIN
};


struct GUI_inf
{
	GUI_TYPES type = GUI_TYPES::NO_TYPES;
	GUI_TYPES subtype = GUI_TYPES::NO_TYPES;
	iPoint pos;
	p2SString text;
};

class GUI;
// ---------------------------------------------------
class j1GUI : public j1Module
{
public:

	j1GUI();

	// Destructor
	virtual ~j1GUI();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	bool AddGui(int x, int y, GUI_TYPES type, GUI_TYPES subtype = GUI_TYPES::NO_TYPES);


	const SDL_Texture* GetAtlas() const;

private:

	void SpawnGUI(const GUI_inf &inf);

	SDL_Texture* atlas;
	p2SString atlas_file_name;

public:
	GUI_inf	queue[MAX_GUI];
	GUI* gui[MAX_GUI];
};

#endif // __j1GUI_H_