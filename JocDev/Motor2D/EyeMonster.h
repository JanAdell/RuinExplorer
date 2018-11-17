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
	bool left;
	const p2DynArray<iPoint>* enemypath;
	bool CleanUp();

	iPoint enemy_pos, player_pos,speed,path_to_follow;
};

#endif
