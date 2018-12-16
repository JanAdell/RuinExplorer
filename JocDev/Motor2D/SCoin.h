#ifndef _SCOIN_H_
#define _SCOIN_H_

#include "Sprites.h"

class Scoin : public Sprites
{
public:
	Scoin(int x, int y);
	~Scoin();

	void Update(float dt);


private:
	Animation SCoin_anim;
};

#endif
