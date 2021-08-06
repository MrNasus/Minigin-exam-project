#include "Minigin.h"

class SanboxGame final : public Game
{

};


Game* CreateGame()
{
	return new SanboxGame{};
}