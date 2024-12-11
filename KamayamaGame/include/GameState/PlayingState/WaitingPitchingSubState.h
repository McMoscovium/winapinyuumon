#pragma once
#include "GameState/GameSubState.h"
#include "GameState/PlayingState/PlayingState.h"

class Game;

class WaitingPitchingSubState :
    public GameSubState<PlayingState>
{
public:
    WaitingPitchingSubState(PlayingState& gameState);
    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};