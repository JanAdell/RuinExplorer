#ifndef _COLLECTIVE_H_
#define _COLLECTIVE_H_

#include "GUI.h"


class Collective : public GUI
{
public:
	Collective(int x, int y);
	~Collective();

	virtual void Update(float dt) = 0;

public:
	uint collect;
};

#endif
