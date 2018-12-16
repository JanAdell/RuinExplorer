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
#include "j1Map.h"
#include "j1Entity.h"
#include "j1Pathfinding.h"
#include "j1Collisions.h"

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
	for (uint i = 0; i < MAX_GUI; ++i)
		if (gui[i] != nullptr)
			gui[i]->Draw((SDL_Texture*)GetAtlas(), dt);

	return true;
}

// Called after all Updates
bool j1GUI::PostUpdate()
{
	

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
	App->scene->changemenu = !App->scene->changemenu;

	for (uint i = 0; i < MAX_GUI; ++i)
	{
		if (gui[i] != nullptr && gui[i]->type == GUI_TYPES::BUTTON)
		{
			gui[i]->to_delete = true;
		}
	}
	switch (GUi.subtype)
	{
	case GUI_TYPES::PLAY:

		App->gui->AddGui(615, 100, GUI_TYPES::BUTTON,GUI_TYPES::EASY);
		App->gui->AddGui(615, 300, GUI_TYPES::BUTTON, GUI_TYPES::DIFFICULT);
		break;

	case GUI_TYPES::DIFFICULT:
		App->gui->dificultEasy = false;
		App->scene->StartGameV();
		App->scene->stayinmenu = false;
		break;

	case GUI_TYPES::EASY:
		App->gui->dificultEasy = true;
		App->scene->StartGameV();
		App->scene->stayinmenu = false;
		break;

	case GUI_TYPES::CONTINUE:

		App->scene->stayinmenu = false;
		App->entities->Start();
		App->fade->fadetoBlack();
		if (App->scene->volcan_map)
		{
			App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
			if (App->map->Load("Volcano_Map.tmx"));
			{
				int w, h;
				uchar* data = NULL;
				if (App->map->CreateWalkabilityMap(w, h, &data))
					App->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);

			}
		}
			App->scene->do_load = false;


		if (!App->scene->volcan_map)
		{
			if (App->map->Load("SeaTempleMap.tmx"));
			{
				int w, h;
				uchar* data = NULL;
				if (App->map->CreateWalkabilityMap(w, h, &data))
					App->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);

			}
			App->audio->PlayMusic("audio/music/AncientRuins.ogg", DEFAULT_MUSIC_FADE_TIME);
		}
		
		break;

	case GUI_TYPES::OPTIONS:
		for (uint i = 0; i < MAX_GUI; ++i)
		{
			if (gui[i] != nullptr && gui[i]->type == GUI_TYPES::BUTTON)
			{
				gui[i]->to_delete = true;
			}
		}
		//create sliderbar

		App->gui->AddGui(615,500,GUI_TYPES::BUTTON,GUI_TYPES :: RETURNMENU);
		break;

	case GUI_TYPES::RETURNMENU:
		if (App->scene->stayinmenu)
		{
			for (uint i = 0; i < MAX_GUI; ++i)
			{
				if (gui[i] != nullptr && gui[i]->type == GUI_TYPES::BUTTON)
				{
					gui[i]->to_delete = true;
				}
			}
		}
		else
		{
			App->scene->die = true;
			App->map->CleanUp();
			App->entities->CleanUp();
			App->gui->CleanUp();
			App->collisions->CleanUp();
			App->pathfinding->CleanUp();
			App->fade->fadetoBlack();
			App->gui->Start();
			App->scene->stayinmenu = true;
		}

		App->scene->GUImenu();
		break;

	case GUI_TYPES::EXIT:
		App->scene->go_out = true;
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

		if (inf.subtype == GUI_TYPES::PAUSE)
			gui[i] = new Pause(inf.pos.x, inf.pos.y);

	case GUI_TYPES::COLLECTIVE:
		if (inf.subtype == GUI_TYPES::COIN)
			gui[i] = new Coins(inf.pos.x, inf.pos.y);
		break;
	}
}

// class Gui ---------------------------------------------------

