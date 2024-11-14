#pragma once
#include "GameSubState.h"

#include "PlayingState.h"
class EndPlayingSubState :
    public GameSubState<PlayingState>
{
private:
public:
    EndPlayingSubState(PlayingState& owner) :
        GameSubState(owner) {}
    ~EndPlayingSubState() = default;

    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

