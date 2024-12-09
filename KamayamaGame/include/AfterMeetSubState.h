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
    //AfterMeetSubState����BallFlyingSubState�Ɉڂ�ɂ������āA�w�i���ς��̂Ń{�[���̃f�[�^���v�Z���Ȃ���
    void translateBall(Ball& ball);
};