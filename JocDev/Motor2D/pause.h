#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "Sprites.h"

class Pause : public Sprites
{
public:
	Pause(int x, int y);
	~Pause();

	void Update(float dt);
private:
	Animation pause_anim;
};

#endif
