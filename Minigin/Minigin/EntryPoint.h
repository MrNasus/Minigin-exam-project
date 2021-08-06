#pragma once

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#endif

#include "MiniginEngine.h"
#include <iostream>
#include "Game.h"

//ayo somebody else fill dis in
extern Game* CreateGame();

int main(int, char* []) {
	std::cout << "main\n";
	dae::MiniginEngine e{};
	e.Initialize();
	e.SetGame(CreateGame());
	return 0;
}