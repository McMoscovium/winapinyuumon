#pragma once

#include "GameObject.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "GameSubState.h"
#include "IGameState.h"

class Game;
class InputManager;

template<typename DerivedState, typename SubState>
class GameState:
	public IGameState
{
protected:
	SubState* currentSubState = nullptr;//�T�u�X�e�[�g�ւ̃|�C���^
public:
	GameState(Game& game) :IGameState(game) {}
	virtual ~GameState() {
		if (currentSubState) {
			delete currentSubState;
			currentSubState = nullptr;
		}
		OutputDebugString(L"�Q�[���X�e�[�g���ύX����܂���\n");
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