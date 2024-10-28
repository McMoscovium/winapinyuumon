#pragma once

class Game;

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void update(Game* game) = 0;
};