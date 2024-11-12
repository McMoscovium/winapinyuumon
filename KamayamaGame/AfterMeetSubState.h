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
    //AfterMeetSubState����BallFlyingSubState�Ɉڂ�ɂ������āA�w�i���ς��̂Ń{�[���̃f�[�^���v�Z���Ȃ���
    void translateBall(Ball& ball);
};

