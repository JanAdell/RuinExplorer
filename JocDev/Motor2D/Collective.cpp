#include "Collective.h"
#include "j1GUI.h"

Collective::Collective(int x, int y, GUI_TYPES subtype):GUI(x,y,GUI_TYPES::COLLECTIVE,subtype)
{
}

Collective::~Collective()
{
}

bool Collective::GetPush()
{
	return false;
}

