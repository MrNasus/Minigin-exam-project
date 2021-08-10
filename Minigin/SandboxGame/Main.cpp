#include "Minigin.h"
#include "SandboxGame.h"

Game* CreateGame()
{
	return new SandboxGame();
}