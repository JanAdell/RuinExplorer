#include "Sprites.h"
#include "j1Gui.h"

Sprites::Sprites(int x, int y, GUI_TYPES subtype) :GUI(x, y,GUI_TYPES::SPRITES,subtype)
{
}

Sprites::~Sprites()
{
}

bool Sprites::GetPush()
{
	return false;
}


