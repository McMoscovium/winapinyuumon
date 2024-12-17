#pragma once

#include "GameState/PlayingState/PlayingState.h"
#include "GameState/GameSubState.h"
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
    bool isMeet(GameObject& ballObject, Ball& ball, Batter& batter, int& hitStopTime);
public:
    InPitchingSubState(PlayingState& ownerState) :GameSubState(ownerState)
    {}
    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

