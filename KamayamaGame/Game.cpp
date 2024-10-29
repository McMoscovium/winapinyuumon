#include "Game.h"
#include"VirtualWindow.h"
#include "TitleScreenState.h"


void Game::drawWindow()
{
}

Game::Game() : currentState(new TitleScreenState()), virtualWindow(nullptr) {}

Game::Game(Window* window) : currentState(new TitleScreenState()), virtualWindow(new VirtualWindow(window)) {}

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

void Game::setBackBuffer(Window* window)
{
}
