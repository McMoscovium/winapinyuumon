#include "Game.h"
#include "VirtualWindow.h"
#include "TitleScreenState.h"
#include "GameState.h"
#include "IGameState.h"

Game::Game(InputManager& inputManager) :
	currentState(nullptr),
	inputManager(inputManager),
	window(nullptr)
{}

Game::~Game() {
	if (currentState) {
		delete currentState;
		currentState = nullptr;
	}
}



bool Game::registerWindow(Window* window)
{
	if (window == nullptr) {
		return false;
	}

	Game::window = window;
	return true;
}

void Game::update() {
	if (currentState) {
		currentState->update(*this);
	}
}

void Game::changeState(IGameState* newState) {
	if (currentState) {
		delete currentState;
	}	
	currentState = newState;
}


IGameState* Game::getCurrentState() const
{
	return currentState;
}