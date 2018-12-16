#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Animation.h"
#include "j1Audio.h"
#include "GUI.h"

class Button : public GUI
{
public:
	Button(int x, int y, GUI_TYPES subtype,p2SString txt);
	~Button();

	void Update(float dt);


	bool GetPush();

private:
	Animation idle;
	Animation push;
	Animation select;

	iPoint buttonsize;
	bool active = false;
	uint clickfx;
};

#endif
