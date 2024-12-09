#pragma once
#include "GameSubState.h"

#include "PlayingState.h"

class GameObject;
class Ball;

class AfterMeetSubState :
    public GameSubState<PlayingState>
{
private:
    const int hitStopTime;
public:
    AfterMeetSubState(PlayingState& owner, const int& hitStopTime) :
        GameSubState(owner),
        hitStopTime(hitStopTime)
    {}

    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;

    void updateBallPos(GameObject& ballObject, Ball& ball, GameObject& shadow);
    //AfterMeetSubStateからBallFlyingSubStateに移るにあたって、背景が変わるのでボールのデータを計算しなおす
    void translateBall(Ball& ball);
};