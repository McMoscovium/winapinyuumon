#pragma once

#include "PlayingState.h"
#include "GameSubState.h"
#include <Windows.h>

class Game;
class Ball;

class InPitchingSubState :
    public GameSubState<PlayingState>
{
private:
    void updatePitchingMotion();
    void updateBall();
    LONG pitchingSpeed=30;//����

    //�{�[���̓�����𒲂ׁA�{�[���̑��x��ݒ�B
    // �������Ă�����true�A�������Ă��Ȃ�������false
    bool calculateMeet(GameObject& ballObject, Ball& ball);
public:
    InPitchingSubState(PlayingState& ownerState) :GameSubState(ownerState)
    {}
    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};
