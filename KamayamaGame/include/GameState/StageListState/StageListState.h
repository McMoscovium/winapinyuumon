#pragma once
#include "GameState/GameState.h"

class Game;

class StageListState :
    public GameState<StageListState,GameSubState<StageListState>>
{
private:
public:
    StageListState(Game& game, AudioManager& audioManager);

    void update(Game& game)override;
	void enter(Game& game)override;
	void exit(Game& game)override;
};

