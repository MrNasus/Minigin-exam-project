#pragma once

#include "Engine.h"
#include <iostream>
#include "Game.h"

extern Game* CreateGame();

using namespace minigin;

int main(int, char* []) {
	std::cout << "main\n";
	Engine e{};
	e.Initialize();
	e.SetGame(CreateGame());
	e.Run();
	return 0;
}