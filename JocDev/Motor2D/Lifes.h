#ifndef _LIFES_H_
#define _LIFES_H_

#include "Sprites.h"
#include "GUI.h"
#include "Animation.h"

class Lifes : public Sprites
{
public:
	Lifes(int x, int y);
	~Lifes();

	void Update(float dt);
private:
	Animation life_anim;
	int max_life, min_life;
};

#endif