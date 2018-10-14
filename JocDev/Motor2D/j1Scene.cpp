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

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	
	//App->map->Load("SeaTempleMap.tmx");
	App->fade->fadetoBlack(2.0f);
	App->map->Load("Volcano_Map.tmx");
	App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
	App->audio->LoadFx("audio/fx/Death.wav");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		if (volcan_map && map_saved)
		{
			App->map->Load("Volcano_Map.tmx");
			App->LoadGame("save_game.xml");
			App->fade->fadetoBlack(2.0f);
			App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);

		}

		if (!volcan_map && !map_saved)
		{
			App->LoadGame("save_game.xml");
			App->fade->fadetoBlack(2.0f);
			App->audio->PlayMusic("audio/music/SeaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
		}
	}
	//fiinish first map
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN && volcan_map)
	{
		App->render->camera.x = App->render->camera.y = 0;
		App->player->position.y = App->map->data.tile_height * 19;
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN && !volcan_map)
	{
		App->render->camera.x = App->render->camera.y = 0;
		App->player->position.y = App->map->data.tile_height * 19;
	}
	
	if (App->player->stay_in_platform)
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		{
			App->SaveGame("save_game.xml");
			if (volcan_map)
				map_saved = true;
			else
				map_saved = false;
		}

	
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		App->map->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack(2.0f);
		App->map->Load("SeaTempleMap.tmx");
		App->audio->PlayMusic("audio/music/AncientRuins.ogg", DEFAULT_MUSIC_FADE_TIME);
		App->render->Start();
		App->player->Start();
		App->collisions->Start();
		App->render->ResetTime(App->render->speed);
		volcan_map = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) 
	{
		App->map->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack(2.0f);
		App->map->Load("Volcano_Map.tmx");
		App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
		App->render->Start();
		App->player->Start();
		App->collisions->Start();
		App->render->ResetTime(App->render->speed);
		volcan_map = true;
	}


	App->map->Draw();


	//dead condition
	if (-App->player->position.y < App->render->camera.y - App->render->camera.h)
	{
		App->player->collider_player_down->to_delete = true;
		App->player->collider_player_up->to_delete = true;
		App->player->collider_player_left->to_delete = true;
		App->player->collider_player_right->to_delete = true;
		App->audio->PlayFx(1, 0);
		App->fade->fadetoBlack(2.0f);
		App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
		App->render->Start();
		App->player->Start();
		App->render->ResetTime(App->render->speed);
		
	}

	//win condicion
	if (-App->player->position.y > -App->map->data.tile_height * 16 && volcan_map)
	{
		
		App->map->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack(2.0f);
		App->map->Load("SeaTempleMap.tmx");
		App->audio->PlayMusic("audio/music/SeaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
		App->render->Start();
		App->player->Start();
		App->collisions->Start();
		App->render->ResetTime(App->render->speed);
		volcan_map = false;
	}
	else if(-App->player->position.y > -App->map->data.tile_height * 10 && !volcan_map)
	{
		App->map->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack(2.0f);
		App->map->Load("Volcano_map.tmx");
		App->audio->PlayMusic("LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
		App->render->Start();
		App->player->Start();
		App->collisions->Start();
		App->render->ResetTime(App->render->speed);
		volcan_map = true;

	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->audio->UnloadFx(1);
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