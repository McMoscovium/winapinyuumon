#include "Game.h"
#include"VirtualWindow.h"
#include "TitleScreenState.h"

Game::Game() : currentState(new TitleScreenState()) {}



void Game::drawWindow()
{
}




Game::~Game() {
    delete currentState;
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
