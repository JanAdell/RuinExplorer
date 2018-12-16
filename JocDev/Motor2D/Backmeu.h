#ifndef _BACKMENU_H_
#define _BACKMENU_H_

#include "Sprites.h"

class backmenu :public Sprites
{
public:
	backmenu(int x, int y);
	~backmenu();

	void Update(float dt);
private:
	Animation open;
	Animation close;
	Animation idle;
	bool closed;
};

#endif