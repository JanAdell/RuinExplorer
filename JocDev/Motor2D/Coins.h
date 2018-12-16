#ifndef _COINS_H_
#define _COINS_H_

#include "Collective.h"

class Coins : public Collective
{
public:
	Coins(int x, int y);
	~Coins();

	void Update(float dt);

	bool Load(pugi::xml_node &node);
	bool Save(pugi::xml_node &node) const;

private:
	Animation coin_anim;
	iPoint size;
	bool collectcoin = false;
};

#endif
