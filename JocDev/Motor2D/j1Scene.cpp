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
#include "Brofiler/Brofiler.h"

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
	//App->fade->fadetoBlack();

	
	App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
	App->audio->LoadFx("audio/fx/death.wav");

	if (App->map->Load("Volcano_Map.tmx"))
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
		
	}
	
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

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
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
		App->entities->enemyboatpos.clear();
		App->entities->enemyeyepos.clear();
		App->entities->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack();
		if (App->map->Load("SeaTempleMap.tmx"))
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
		App->player->Start();
		App->collisions->Start();
		App->render->ResetTime(App->render->speed);
		volcan_map = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) 
	{
		
		App->map->CleanUp();
		App->entities->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack();
		if (App->map->Load("Volcano_Map.tmx"))
		{
			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);

		}
		App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
		App->render->Start();
		App->player->Start();
		App->entities->Start();
		App->collisions->Start();
		App->render->ResetTime(App->render->speed);
		volcan_map = true;
	}


	App->map->Draw();


	//dead condition
	if (-App->player->position.y < App->render->camera.y - App->render->camera.h)
	{
		death();		
	}

	//win condition
	if (-App->player->position.y > -App->map->data.tile_height * 16 && volcan_map)
	{
		
		App->map->CleanUp();
		App->entities->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack();
		if (App->map->Load("SeaTempleMap.tmx"))
		{
			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);

		}
		App->audio->PlayMusic("audio/music/AncientRuins.ogg", DEFAULT_MUSIC_FADE_TIME);
		App->render->Start();
		App->player->Start();
		App->entities->Start();
		App->collisions->Start();
		App->render->ResetTime(App->render->speed);
		volcan_map = false;
	}
	else if(-App->player->position.y > -App->map->data.tile_height * 10 && !volcan_map)
	{
		App->map->CleanUp();
		App->entities->CleanUp();
		App->collisions->CleanUp();
		App->fade->fadetoBlack();
		if (App->map->Load("Volcano_Map.tmx"))
		{
			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);

		}
		App->audio->PlayMusic("audio/music/LavaLand.ogg", DEFAULT_MUSIC_FADE_TIME);
		App->render->Start();
		App->player->Start();
		App->entities->Start();
		App->collisions->Start();
		App->render->ResetTime(App->render->speed);
		volcan_map = true;

	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateScene", Profiler::Color::Brown);

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

void j1Scene::death()
{
	
	if (App->player->collider_player_down != nullptr)
		App->player->collider_player_down->to_delete = true;
	if (App->player->collider_player_up != nullptr)
		App->player->collider_player_up->to_delete = true;
	if (App->player->collider_player_left != nullptr)
		App->player->collider_player_left->to_delete = true;
	if (App->player->collider_player_right != nullptr)
		App->player->collider_player_right->to_delete = true;
	if (App->player->collider_player != nullptr)
		App->player->collider_player->to_delete = true;
	if (App->player->cameralimit != nullptr)
		App->player->cameralimit->to_delete = true;
	App->entities->CleanUp();
	App->audio->PlayFx(1, 0);
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
	App->player->Start();
	App->render->ResetTime(App->render->speed);
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
}

