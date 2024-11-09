#include "Game.h"
#include "TitleScreenState.h"
#include "GameState.h"
#include "AudioManager.h"

using namespace std;

Game::Game() :
	currentState(make_unique<TitleScreenState>(*this))
{}

Game::~Game() {
}




void Game::termination()
{
}

const InputManager& Game::getConstInputManager()const
{
	return inputManager;
}

InputManager& Game::getInputManager()
{
	return inputManager;
}

const std::unique_ptr<IGameState>& Game::getCurrentState()const
{
	return currentState;
}
