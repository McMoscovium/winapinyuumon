#pragma once
#include "PitchType.h"

class Ball;
class Pitcher;

class Straight :
    public PitchType
{
private:
    const float acceleration = 2.0f;//始端に対する終端の見かけの速度の倍率（力学的に定義される加速度とは異なる）
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

