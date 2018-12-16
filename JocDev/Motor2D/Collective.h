#ifndef _COLLECTIVE_H_
#define _COLLECTIVE_H_

#include "GUI.h"


class Collective : public GUI
{
public:
	Collective(int x, int y, GUI_TYPES subtype);
	~Collective();

	virtual void Update(float dt) = 0;
	bool GetPush();
public:
	uint collect;
};

#endif
