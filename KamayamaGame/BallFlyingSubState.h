#pragma once
#include "GameSubState.h"

#include "PlayingState.h"

class Game;
class Ball;

class BallFlyingSubState :
    public GameSubState<PlayingState>
{
private:
    void updateBall(Ball& ball);
public:
    BallFlyingSubState(PlayingState& owner);
    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

