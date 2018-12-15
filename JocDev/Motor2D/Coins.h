#ifndef _COINS_H_
#define _COINS_H_

#include "Collective.h"

class Coins : public Collective
{
public:
	Coins(int x, int y);
	~Coins();

	void Update(float dt);

private:
	Animation coin_anim;
	iPoint size;
	bool collectcoin = false;
};

#endif
