#pragma once
#include "Stadium.h"
class TheHundredAcreWoodStadium :
    public Stadium
{
public:
    TheHundredAcreWoodStadium() :
        Stadium() {}
    ~TheHundredAcreWoodStadium() = default;
    PlayingState::FlyBallResult result(POINT pos)override;
};

