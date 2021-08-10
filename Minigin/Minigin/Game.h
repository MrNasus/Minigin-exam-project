#pragma once

class Game
{
public:
	Game() = default;
	virtual ~Game() = default;

	virtual void Load() = 0;
};