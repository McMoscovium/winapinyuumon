#pragma once

#include "PlayingState.h"
#include "GameSubState.h"

class Game;

class InPitchingSubState :
    public GameSubState<PlayingState>
{
private:
    void updatePitchingMotion();
public:
    InPitchingSubState(PlayingState& ownerState) :GameSubState(ownerState)
    {}
    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

