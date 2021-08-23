#include "Minigin.h"
#include "Galaga.h"

Game* CreateGame()
{
	return new Galaga();
}