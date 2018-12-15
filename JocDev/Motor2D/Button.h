#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Animation.h"
#include "j1Audio.h"
#include "GUI.h"

class Button : public GUI
{
public:
	Button(int x, int y);
	~Button();

	void Update(float dt);


private:
	Animation idle;
	Animation push;
	Animation select;

	iPoint buttonsize;
};

#endif
