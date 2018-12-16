#ifndef _CREDITS_H_
#define _CREDITS_H_

#include "Sprites.h"

class credits : public Sprites
{
public:
	credits(int x, int y);
	~credits();
	void Update(float dt);
private:
	Animation credits_anim;
};

#endif