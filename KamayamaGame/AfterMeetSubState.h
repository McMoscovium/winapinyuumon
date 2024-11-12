#pragma once
#include "GameSubState.h"

#include "PlayingState.h"

class GameObject;
class Ball;

class AfterMeetSubState :
    public GameSubState<PlayingState>
{
private:
public:
    AfterMeetSubState(PlayingState& owner) :
        GameSubState(owner) {}
    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;

    void updateBallPos(GameObject& ballObject, Ball& ball);
    //AfterMeetSubStateからBallFlyingSubStateに移るにあたって、背景が変わるのでボールのデータを計算しなおす
    void translateBall(Ball& ball);
};

