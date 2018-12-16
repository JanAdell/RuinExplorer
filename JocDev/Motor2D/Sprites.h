#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "GUI.h"

class Sprites : public GUI
{
public:
	Sprites(int x, int y, GUI_TYPES subtype);
	~Sprites();

	virtual void Update(float dt) = 0;
	bool GetPush();

};
#endif
