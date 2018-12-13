//#include "j1App.h"
//#include "j1Input.h"
//#include "j1Render.h"
//#include "j1UI.h"
//#include "j1Textures.h"
//#include "Entity.h"
//#include "j1Audio.h"
//#include "j1Player.h"
//#include "j1Scene.h"
//#include "p2Log.h"
//#include "j1Collisions.h"
//#include "Brofiler/Brofiler.h"
//
//#define SCREEN_SIZE 1
//
//j1UI::j1UI()
//{
//	name.create("UI");
//	for (uint i = 0; i < MAX_UI; ++i)
//		UI[i] = nullptr;
//}
//
//// Destructor
//j1UI::~j1UI()
//{
//}
//
//bool j1UI::Start()
//{
//	sprites = App->tex->Load("../Game/maps/enemy.png");
//	return true;
//}
//
//bool j1UI::PreUpdate()
//{
//	//BROFILER_CATEGORY("PreUpdateEntity", Profiler::Color::Pink);
//	// check camera position to decide what to spawn
//
//	return true;
//}
//
//// Called before render is available
//bool j1UI::Update(float dt)
//{
//	BROFILER_CATEGORY("UpdateEntity", Profiler::Color::LightPink);
//
//	for (uint i = 0; i < MAX_UI; ++i)
//		if (entities[i] != nullptr)
//			entities[i]->Update(dt);
//
//	for (uint i = 0; i < MAX_UI; ++i)
//		if (entities[i] != nullptr)
//			entities[i]->Draw(sprites);
//
//	return true;
//}
//
//
//// Called before quitting
//bool j1UI::CleanUp()
//{
//	LOG("Freeing all enemies");
//
//	App->tex->UnLoad(sprites);
//
//	for (uint i = 0; i < MAX_UI; ++i)
//	{
//		if (entities[i] != nullptr)
//		{
//			delete entities[i];
//			entities[i] = nullptr;
//		}
//	}
//
//
//	return true;
//}
//
//bool j1UI::AddUI(UI_TYPES type, int x, int y)
//{
//	bool ret = false;
//
//	for (uint i = 0; i < MAX_UI; ++i)
//	{
//		if (queue[i].type == UI_TYPES::NO_TYPE)
//		{
//			queue[i].type = type;
//			queue[i].x = x;
//			queue[i].y = y;
//			ret = true;
//			break;
//		}
//	}
//
//	return ret;
//}
//
//
//void j1UI::SpawnUI(const UIInfo& info)
//{
//	// find room for the new enemy
//	/*uint i = 0;
//	for (; entities[i] != nullptr && i < MAX_UI; ++i);
//	switch (info.type)
//	{
//	case UI_TYPES::ENTITY_PLAYER:
//		entities[i] = new Player(info.x, info.y);
//		player = entities[i];
//		break;
//	case UI_TYPES::ENTITY_EYEMONSTER:
//		entities[i] = new EyeMonster(info.x, info.y);
//		break;
//	case UI_TYPES::ENTITY_BOAR:
//		entities[i] = new boar(info.x, info.y);
//		break;
//	}*/
//
//}
//
//void j1UI::OnCollision(Collider* c1, Collider* c2)
//{
//	/*for (uint i = 0; i < MAX_UI; ++i)
//	{
//		if (entities[i] != nullptr && entities[i]->GetCollider() == c1)
//		{
//			if (c1->type == COLLIDER_PLAYER)
//				entities[i]->OnCollision(c2);
//			else
//				entities[i]->OnCollision(c2);
//			if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER)
//			{
//				delete entities[i];
//				entities[i] = nullptr;
//			}
//		}
//
//	}*/
//}


#include "j1UI.h"

j1UI::j1UI()
{

}

j1UI::~j1UI()
{
}

bool j1UI::Start()
{
	return true;
}

bool j1UI::Update(float dt)
{
	return true;
}

bool j1UI::CleanUp()
{
	return true;
}
