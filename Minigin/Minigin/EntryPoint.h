#pragma once

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#endif

#include "Engine.h"
#include <iostream>
#include "Game.h"

//ayo somebody else fill dis in
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