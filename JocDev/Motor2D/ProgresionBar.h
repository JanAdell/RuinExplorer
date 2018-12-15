#ifndef _PROGRESIONBAR_H_
#define _PROGRESIONBAR_H_

#include "Sprites.h"

class ProgresionBar : public Sprites
{
public:
	ProgresionBar(int x, int y);
	~ProgresionBar();
	void Update(float dt);
private:
	Animation progresbar_anim;
};

#endif
