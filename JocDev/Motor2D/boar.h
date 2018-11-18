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
	virtual bool Load(pugi::xml_node &node);
	virtual	bool Save(pugi::xml_node &node) const;
	bool CleanUp();
public:
	bool left;
	const p2DynArray<iPoint>* enemypath;


	iPoint enemy_pos, player_pos, speed, objective;
};

#endif