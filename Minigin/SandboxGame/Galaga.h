#pragma once
#include "Game.h"
#include "Gamemode.h"
class Galaga final : public Game
{
public:

	Galaga();
	~Galaga();

	void Load() override;

	void LoadGame(Gamemode gamemode, bool reload);
private:
	void LoadMainMenu();
	void LoadPauseMenu();
	void LoadGameOver();
};

