#pragma once

#include "GameSubState.h"
#include "PlayingState.h"

class Game;

class CutIn :
    public GameSubState<PlayingState>
{
private:
    const int hitStopTime;
public:
    CutIn(PlayingState& owner, const int& hitStopTime):
        GameSubState<PlayingState>(owner),
        hitStopTime(hitStopTime)
    {}
    ~CutIn() = default;

    void enter(Game& game)override;
    void update(Game& game)override;
    void exit(Game& game)override;
};