#pragma once
#include "GameSubState.h"
#include "PlayingState.h"
#include <string>


class BattingResultSubState :
    public GameSubState<PlayingState>
{
private:
    PlayingState::FlyBallResult result;
    std::wstring resultString()const;
public:
    BattingResultSubState(PlayingState& owner, PlayingState::FlyBallResult result) :
        GameSubState(owner),
        result(result) {}
    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

