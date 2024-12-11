#pragma once
#include "PitchType.h"

class Ball;

class Straight :
    public PitchType
{
private:
public:
    Straight() :
        PitchType(L"Straight") {}

    void setBallVelocity(Ball& ball, int frame)override;
};

