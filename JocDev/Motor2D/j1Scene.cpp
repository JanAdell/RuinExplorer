#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1FadetoBlack.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Collisions.h"
#include "j1Entity.h"
#include "j1Pathfinding.h"
#include "j1GUI.h"
#include "Brofiler/Brofiler.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& conf)
{
	LOG("Loading Scene");
	menu_file_name = conf.child("menu").attribute("name").as_string("");
	menu_file_name2 = conf.child("menu2").attribute("name").as_string("");
	rect = {conf.child("menu").attribute("x").as_int(),conf.child("menu").attribute("y").as_int(),conf.child("menu").attribute("w").as_int(),conf.child("menu").attribute("h").as_int() };
	rectR = { conf.child("menu2").attribute("x").as_int(),conf.child("menu2").attribute("y").as_int(),conf.child("menu2").attribute("w").as_int(),conf.child("menu2").attribute("h").as_int() };
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->entities->CleanUp();
	App->collisions->CleanUp();
	App->map->CleanUp();
	menuBackground = App->tex->Load(menu_file_name.GetString());
	menuBackgroundR = App->tex->Load(menu_file_name2.GetString());
	GUImenu();
	App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateScene", Profiler::Color::SaddleBrown);

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::RosyBrown);
	if (stayinmenu)
	{
		if(changemenu)
			App->render->Blit(menuBackground, 0, 0, SDL_RendererFlip::SDL_FLIP_NONE, &rect, 0.0f);
		else
			App->render->Blit(menuBackgroundR, 0, 0, SDL_RendererFlip::SDL_FLIP_NONE, &rect, 0.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		do_load = true;
	if(do_load)
	{
		if (volcan_map && map_saved)
		{
			App->LoadGame("save_game.xml");
			App->fade->fadetoBlack();
			App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);

		}

		if (!volcan_map && !map_saved)
		{
			App->LoadGame("save_game.xml");
			App->fade->fadetoBlack();
			App->audio->PlayMusic("audio/music/AncientRuins.ogg", DEFAULT_MUSIC_FADE_TIME);
		}
		do_load = false;
	}
	//fiinish first map
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN && volcan_map)
	{
		App->render->camera.x = App->render->camera.y = 0;
		App->entities->player->position.y = App->map->data.tile_height * 19;
	}

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && !volcan_map)
	{
		App->render->camera.x = App->render->camera.y = 0;
		App->entities->player->position.y = App->map->data.tile_height * 19;
	}
	if (App->entities->player != nullptr)
	{
		if (App->entities->player->stay_in_platform)
			if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
			{
				App->SaveGame("save_game.xml");
				if (volcan_map)
					map_saved = true;
				else
					map_saved = false;
			}

	}
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN && !stayinmenu)
	{
		StartGameT();
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && !stayinmenu) 
	{
		StartGameV();
	}
	//open pause
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && !App->dopause && !stayinmenu)
	{
		App->gui->AddGui(300, 120, GUI_TYPES::SPRITES, GUI_TYPES::PAUSE);
		App->gui->AddGui(400, 440, GUI_TYPES::BUTTON, GUI_TYPES::RETURNMENU);
		App->gui->AddGui(400, 240, GUI_TYPES::BUTTON, GUI_TYPES::OPTIONSPAUSE);
	}

	//close pause
	else if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && App->dopause && !stayinmenu)
	{
		for (uint i = 0; i < MAX_GUI; ++i)
		{
			if (App->gui->gui[i] != nullptr && (App->gui->gui[i]->type == GUI_TYPES::BUTTON || App->gui->gui[i]->subtype == GUI_TYPES::PAUSE))
			{
				App->gui->gui[i]->to_delete = true;
			}
		}
	}
	App->map->Draw();


	//dead condition
	if (App->entities->player != nullptr)
	{
		if (-App->entities->player->position.y < App->render->camera.y - App->render->camera.h)
		{
			App->audio->PlayFx(deathsfx);
			death();
		}
	}
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateScene", Profiler::Color::Brown);

	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		go_out = true;
	if(go_out)
		ret = false;

	die = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->audio->UnloadFx(deathsfx);
	return true;

}


// Load Game State
bool j1Scene::Load(pugi::xml_node& data)
{
	volcan_map = data.child("scene").attribute("volcan_map").as_bool();
	return true;
}

// Save Game State
bool j1Scene::Save(pugi::xml_node& data) const
{
	pugi::xml_node scene = data.append_child("scene");

	scene.append_attribute("volcan_map") = volcan_map;
	
	return true;
}

void j1Scene::death()
{
	App->scene->die = true;
	App->entities->CleanUp();
	App->fade->fadetoBlack();
	if (volcan_map)
	{
		App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
	}
	else
	{
		App->audio->PlayMusic("audio/music/AncientRuins.ogg", DEFAULT_MUSIC_FADE_TIME);
	}
	App->entities->Start();
	App->render->Start();
	respawnEnemies();
}

void j1Scene::respawnEnemies()
{

	for (p2List_item<iPoint> *iterator = App->entities->enemyboatpos.start; iterator != nullptr;iterator = iterator->next)
	{
		App->entities->AddEntity(ENTITY_TYPES::ENTITY_BOAR, iterator->data.x, iterator->data.y);
	}

	
	for (p2List_item<iPoint> *iterator = App->entities->enemyeyepos.start; iterator != nullptr;iterator = iterator->next)
	{
		App->entities->AddEntity(ENTITY_TYPES::ENTITY_EYEMONSTER, iterator->data.x, iterator->data.y);
	}

	App->entities->AddEntity(ENTITY_TYPES::ENTITY_PLAYER, App->entities->position_player.x, App->entities->position_player.y);
}

void j1Scene::respawnGUI()
{
	App->gui->AddGui(250, 13, GUI_TYPES::SPRITES, GUI_TYPES::LIFES);
	App->gui->AddGui(300, 10, GUI_TYPES::SPRITES, GUI_TYPES::SPRITECOIN);
	App->gui->AddGui(965, 740, GUI_TYPES::SPRITES, GUI_TYPES::BAR);
	App->gui->AddGui(950, 500, GUI_TYPES::SPRITES, GUI_TYPES::PROGRESBAR);
	for (p2List_item<iPoint>* item = App->gui->coins.start; item != nullptr; item = item->next)
	{
		App->gui->AddGui(item->data.x, item->data.y, GUI_TYPES::COLLECTIVE, GUI_TYPES::COIN);
	}
}

void j1Scene::GUImenu()
{
	changemenu = true;
	App->gui->AddGui(130, 100, GUI_TYPES::BUTTON,GUI_TYPES::PLAY);
	App->gui->AddGui(130, 250, GUI_TYPES::BUTTON, GUI_TYPES::CONTINUE);
	App->gui->AddGui(130, 400, GUI_TYPES::BUTTON, GUI_TYPES::OPTIONS);
	App->gui->AddGui(130, 550, GUI_TYPES::BUTTON, GUI_TYPES::EXIT);
	App->gui->AddGui(10, 10, GUI_TYPES::TEXTBOX, GUI_TYPES::NO_TYPES, "hello world");

}

void j1Scene::StartGameV()
{
	App->map->CleanUp();
	App->entities->CleanUp();
	App->gui->CleanUp();
	App->collisions->CleanUp();
	App->pathfinding->CleanUp();
	App->fade->fadetoBlack();
	if (App->map->Load("Volcano_Map.tmx"));
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

	}
	App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
	App->render->Start();
	App->entities->Start();
	App->gui->Start();
	App->collisions->Start();
	volcan_map = true;
}

void j1Scene::StartGameT()
{
	App->map->CleanUp();
	App->entities->CleanUp();
	App->collisions->CleanUp();
	App->gui->CleanUp();
	App->pathfinding->CleanUp();
	App->fade->fadetoBlack();
	if (App->map->Load("SeaTempleMap.tmx"));
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

	}
	App->audio->PlayMusic("audio/music/AncientRuins.ogg", DEFAULT_MUSIC_FADE_TIME);
	App->render->Start();
	App->entities->Start();
	App->gui->Start();
	App->collisions->Start();
	volcan_map = false;
}

