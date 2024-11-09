#pragma once

#include "GameObject.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "GameSubState.h"
#include "IGameState.h"


class Game;
class InputManager;


bool isPointOnRect(POINT point, RECT rect);

template <typename StateType>
class GameState : public IGameState
{
	using SubStateType = GameSubState<StateType>;
protected:
	//subState
	std::unique_ptr<SubStateType> currentSubState;

public:
	GameState(Game& game) :IGameState(game) {}
	virtual ~GameState() = default;
	
	//
	void changeSubState(
		std::unique_ptr<SubStateType> newSubState
	) {
		currentSubState = std::move(newSubState);
	}
};