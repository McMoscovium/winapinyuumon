#include "Game.h"

#include "TitleScreenState.h"


Game::Game() : currentState(new TitleScreenState()) {}

Game::~Game() {
    delete currentState;
}
void Game::update() {
	currentState->update(this);
}

void Game::changeState(GameState* newState) {
	delete currentState;
	currentState = newState;
}