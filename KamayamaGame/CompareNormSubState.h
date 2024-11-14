#pragma once
#include "GameSubState.h"

#include "PlayResultState.h"
class CompareNormSubState :
    public GameSubState<PlayResultState>
{
private:
public:
    CompareNormSubState(PlayResultState& owner) :
        GameSubState(owner) {}
    ~CompareNormSubState() = default;

    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

