#pragma once
#include "GameSubState.h"
#include "PlayingState.h"

class AfterBallLandingSubState :
    public GameSubState<PlayingState>
{
private:
public:
    AfterBallLandingSubState(PlayingState& owner) :
        GameSubState(owner) {}
    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

