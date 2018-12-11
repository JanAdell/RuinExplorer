#ifndef __EyeMonster_H__
#define __EyeMonster_H__

#include "Entity.h"
#include "p2DynArray.h"

class EyeMonster : public Entity
{
private:
	Animation eyemonster;
	
public:

	EyeMonster(int x, int y);
	~EyeMonster() {};
	void Update(float dt);
	void OnCollision(Collider* collider);
	virtual bool Load(pugi::xml_node &node);
	virtual	bool Save(pugi::xml_node &node) const;
	bool CleanUp();
public:
	bool left;
	const p2DynArray<iPoint>* enemypath;
	uint alpha = 80;
	int search;
	iPoint enemy_pos, player_pos,speed,objective;
	bool diferentpath = false;
};

#endif
