#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1GUI.h"

j1GUI::j1GUI() : j1Module()
{
	name.create("gui");
	for (uint i = 0; i < MAX_GUI; ++i)
		gui[i] = nullptr;
}

// Destructor
j1GUI::~j1GUI()
{}

// Called before render is available
bool j1GUI::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1GUI::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1GUI::PreUpdate()
{
	for (uint i = 0; i < MAX_GUI; ++i)
	{
		if (queue[i].type != GUI_TYPES::NO_TYPES)
		{
			SpawnGUI(queue[i]);
			queue[i].type = GUI_TYPES::NO_TYPES;
		}
	}


	return true;
}

bool j1GUI::Update(float dt)
{
	for (uint i = 0; i < MAX_GUI; ++i)
		if (gui[i] != nullptr)
			gui[i]->Update(dt);

	return true;
}

// Called after all Updates
bool j1GUI::PostUpdate()
{
	for (uint i = 0; i < MAX_GUI; ++i)
		if (gui[i] != nullptr)
			gui[i]->Draw((SDL_Texture*)GetAtlas());

	return true;
}

// Called before quitting
bool j1GUI::CleanUp()
{
	LOG("Freeing GUI");
	App->tex->UnLoad(atlas);

	for (uint i = 0; i < MAX_GUI; ++i)
	{
		if (gui[i] != nullptr)
		{
			delete gui[i];
			gui[i] = nullptr;
		}
	}
	coins.clear();

	return true;
}

bool j1GUI::AddGui(int x, int y, GUI_TYPES type, GUI_TYPES subtype)
{
	bool ret = false;

	for (uint i = 0; i < MAX_GUI; ++i)
	{
		if (queue[i].type == GUI_TYPES::NO_TYPES)
		{
			queue[i].type = type;
			queue[i].subtype = subtype;
			queue[i].pos.x = x;
			queue[i].pos.y = y;
			ret = true;
			break;
		}
	}

	return ret;
}


// const getter for atlas
const SDL_Texture* j1GUI::GetAtlas() const
{
	return atlas;
}

void j1GUI::SpawnGUI(const GUI_inf & inf)
{
	uint i = 0;
	for (; gui[i] != nullptr && i < MAX_GUI; ++i);
	switch (inf.type)
	{
	case GUI_TYPES::BUTTON:
		gui[i] = new Button(inf.pos.x, inf.pos.y);
		break;
	case GUI_TYPES::SPRITES:
		if (inf.subtype == GUI_TYPES::LIFES)
			gui[i] = new Lifes(inf.pos.x, inf.pos.y);

		if (inf.subtype == GUI_TYPES::PROGRESBAR)
			gui[i] = new ProgresionBar(inf.pos.x, inf.pos.y);

		if (inf.subtype == GUI_TYPES::BAR)
			gui[i] = new bar(inf.pos.x, inf.pos.y);

		if (inf.subtype == GUI_TYPES::SPRITECOIN)
			gui[i] = new Scoin(inf.pos.x, inf.pos.y);
		break;
	case GUI_TYPES::COLLECTIVE:
		if (inf.subtype == GUI_TYPES::COIN)
			gui[i] = new Coins(inf.pos.x, inf.pos.y);
		break;
	}
}

// class Gui ---------------------------------------------------

