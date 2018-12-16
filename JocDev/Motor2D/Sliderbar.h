#ifndef _SLIDERBAR_H_
#define _SLIDERBAR_H_

#include "GUI.h"

class sliderbar :public GUI
{
public:
	sliderbar(int x, int y);
	~sliderbar();

	void Update(float dt);

private:
	Animation slider_anim;
};

#endif
