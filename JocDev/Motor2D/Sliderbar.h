#ifndef _SLIDERBAR_H_
#define _SLIDERBAR_H_

#include "GUI.h"

class sliderbar :public GUI
{
public:
	sliderbar(int x, int y);
	~sliderbar();

	void Update(float dt);
	bool GetPush();
private:
	Animation anim;
	iPoint size,mousepos;
	float pich;
};

#endif
