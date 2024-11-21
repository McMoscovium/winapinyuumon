#pragma once
#include "GameState.h"

class Game;

class StageListState :
    public GameState<StageListState,GameSubState<StageListState>>
{
private:
public:
    StageListState(Game& game);

    void update(Game& game)override;
};

