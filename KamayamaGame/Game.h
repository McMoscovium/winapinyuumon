#pragma once

#include <Windows.h>

class GameState;
class TitleScreenState;

class Game
{
private:
	GameState* currentState;
	
public:
	Game();
	~Game();

	void update();

	void changeState(GameState* newState);
};