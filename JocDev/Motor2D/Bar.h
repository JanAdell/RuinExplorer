#ifndef _BAR_H_
#define _BAR_H_

#include "Sprites.h"

class bar : public Sprites
{
public:
	bar(int x, int y);
	~bar();

	void Update(float dt);
public:
	Animation bar_anim;
private:
	uint prevframe;
	iPoint barpos;
};

#endif

