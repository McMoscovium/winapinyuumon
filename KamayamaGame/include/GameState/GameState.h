#pragma once

#include "GameObject/GameObject.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "GameState/GameSubState.h"
#include "IGameState.h"

class Game;
class InputManager;

template<typename DerivedState, typename SubState>
class GameState:
	public IGameState
{
protected:
	SubState* currentSubState = nullptr;//サブステートへのポインタ
public:
	GameState(Game& game) :IGameState(game) {}
	virtual ~GameState() {
		if (currentSubState) {
			delete currentSubState;
			currentSubState = nullptr;
		}
	}

	virtual void update(Game& game) = 0;

	//
	virtual void changeSubState(SubState* newSubState) {
		if (currentSubState) {
			currentSubState->exit(game);
			delete currentSubState;
		}
		currentSubState = newSubState;
		currentSubState->enter(game);
	}
};