#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1GUI.h"
#include "j1FadetoBlack.h"
#include "j1Scene.h"

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

	for (uint i = 0; i < MAX_GUI; ++i)
	{
		if (gui[i] != nullptr && gui[i]->to_delete == true)
		{
			delete gui[i];
			gui[i] = nullptr;
		}
	}
	return true;
}

bool j1GUI::Update(float dt)
{
	for (uint i = 0; i < MAX_GUI; ++i)
		if (gui[i] != nullptr)
			gui[i]->Update(dt);

	for (uint i = 0; i < MAX_GUI; ++i)
	{
		if (gui[i] != nullptr)
		{
			if (gui[i]->GetPush() == true)
			{
				ActiveBotton(*gui[i]);
			}
		}
	}

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

bool j1GUI::Load(pugi::xml_node & data)
{
	for (uint i = 0; i < MAX_GUI; i++)
	{
		if (gui[i] != nullptr)
		{
			if (gui[i]->type == GUI_TYPES::BUTTON)
			{
				pugi::xml_node button_data = data.child("Button");
				gui[i]->Load(button_data);
			}
			if (queue[i].type == GUI_TYPES::COLLECTIVE)
			{
				pugi::xml_node collective_data = data.child("Collective");
				gui[i]->Load(collective_data);
			}
			if (queue[i].type == GUI_TYPES::SPRITES)
			{
				pugi::xml_node sprites_data = data.child("Sprites");
				gui[i]->Load(sprites_data);
			}
		}
	}
	return true;
}

bool j1GUI::Save(pugi::xml_node & data) const
{
	for (uint i = 0; i < MAX_GUI; i++)
	{
		if (gui[i] != nullptr)
		{
			if (gui[i]->type == GUI_TYPES::BUTTON)
			{
				pugi::xml_node button_data = data.append_child("Button");
				gui[i]->Save(button_data);
			}
			if (gui[i]->type == GUI_TYPES::COLLECTIVE)
			{
				pugi::xml_node collective_data = data.append_child("Collective");
				gui[i]->Save(collective_data);
			}
			if (gui[i]->type == GUI_TYPES::SPRITES)
			{
				pugi::xml_node sprites_data = data.append_child("Sprites");
				gui[i]->Save(sprites_data);
			}
		}
	}
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

void j1GUI::ActiveBotton(GUI & GUi)
{
	switch (GUi.subtype)
	{
	case GUI_TYPES::PLAY:

		for (uint i = 0; i < MAX_GUI; ++i)
		{
			if (gui[i] != nullptr && gui[i]->type == GUI_TYPES::BUTTON)
			{
				gui[i]->to_delete = true;
			}
		}
		App->gui->AddGui(100, 100, GUI_TYPES::BUTTON,GUI_TYPES::EASY);
		App->gui->AddGui(100, 300, GUI_TYPES::BUTTON, GUI_TYPES::DIFFICULT);
		break;

	case GUI_TYPES::DIFFICULT:
		App->gui->dificultEasy = false;
		App->scene->StartGameV();
		break;

	case GUI_TYPES::EASY:
		App->gui->dificultEasy = true;
		App->scene->StartGameV();
		break;

	case GUI_TYPES::CONTINUE:
		
		if (App->scene->volcan_map && App->scene->map_saved)
		{
			App->scene->StartGameV();
			App->LoadGame("save_game.xml");
			App->fade->fadetoBlack();
			App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
		}

		if (!App->scene->volcan_map && !App->scene->map_saved)
		{
			App->LoadGame("save_game.xml");
			App->fade->fadetoBlack();
			App->audio->PlayMusic("audio/music/AncientRuins.ogg", DEFAULT_MUSIC_FADE_TIME);
		}
		break;
	}
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
		gui[i] = new Button(inf.pos.x, inf.pos.y,inf.subtype);
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

