#pragma once
#include "Game.h"
class SandboxGame final : public Game
{
public:
	SandboxGame();
	~SandboxGame();

	void Load() override;
};

