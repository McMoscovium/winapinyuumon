#include "Game.h"
#include "VirtualWindow.h"
#include "TitleScreenState.h"
#include "GameState.h"

Game::Game() : currentState(new TitleScreenState()) {}



void Game::drawWindow()
{
}

Game::~Game() {
}
void Game::update(InputManager* inputManager) {
	currentState->update(this, inputManager);
}

void Game::changeState(GameState* newState) {
	delete currentState;
	currentState = newState;
}

void Game::setBackBuffer(Window* window)
{
}

const GameState* Game::getCurrentState() const
{
	return currentState;
}

void Game::termination()
{
	delete currentState;
}

