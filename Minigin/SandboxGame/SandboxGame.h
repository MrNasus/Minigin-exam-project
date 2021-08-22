#pragma once
#include "Game.h"
#include "Gamemode.h"
class SandboxGame final : public Game
{
public:

	SandboxGame();
	~SandboxGame();

	void Load() override;

	void LoadGame(Gamemode gamemode, bool reload);
private:
	void LoadMainMenu();
	void LoadPauseMenu();
};

