#pragma once
#include "PitchType.h"

class Ball;
class Pitcher;

class Straight :
    public PitchType
{
private:
    const float acceleration = 2.0f;//�n�[�ɑ΂���I�[�̌������̑��x�̔{���i�͊w�I�ɒ�`���������x�Ƃ͈قȂ�j
public:
    Straight() :
        PitchType(L"Straight") {}

    Straight(const float accel) :
        PitchType(L"Straight"),
        acceleration(accel) {
    }

    void update(Ball& ball, int frame)override;

    virtual float decideAngle()override;
    float decideHVelocity()override { return 0; }
    int decideVelocity(Pitcher& pitcher)override;
};

