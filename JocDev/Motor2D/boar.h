#ifndef __boar_H__
#define __boar_H__

#include "Entity.h"
#include "p2DynArray.h"

class boar : public Entity
{
private:
	Animation boaranim;

public:

	boar(int x, int y);
	~boar() {};
	void Update(float dt);
	void OnCollision(Collider* collider);
	bool Load(pugi::xml_node &node);
	bool Save(pugi::xml_node &node) const;
public:
	bool left;
	const p2DynArray<iPoint>* enemypath;
	int search;
	int next_ground;
	iPoint enemy_pos, objective, player_pos,ground;
	fPoint speed;
};

#endif