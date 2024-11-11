#pragma once
#include "GameSubState.h"

#include "PlayingState.h"

class AfterMeetSubState :
    public GameSubState<PlayingState>
{
private:
public:
    AfterMeetSubState(PlayingState& owner);

    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;

    void updateBall();
};

