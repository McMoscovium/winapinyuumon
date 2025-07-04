#include "Game/Game.h"
#include "GameState/TitleScreenState/TitleScreenState.h"
#include "GameState/GameState.h"
#include "GameState/IGameState.h"

Game::Game(InputManager& inputManager, const HINSTANCE& hInstance) :
	currentState(nullptr),
	inputManager(inputManager),
	window(nullptr),
	hInstance(hInstance)
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
		currentState->exit(*this);
		delete currentState;
	}
	currentState = newState;
	currentState->enter(*this);
}


IGameState* Game::getCurrentState() const
{
	return currentState;
}

const HINSTANCE& Game::getHInstance()
{
	return hInstance;
}
