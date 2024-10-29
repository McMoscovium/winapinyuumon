#pragma once

class Game;
class InputManager;

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void update(Game* game,InputManager* inputManager) = 0;
};