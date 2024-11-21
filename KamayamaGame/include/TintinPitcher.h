#pragma once
#include "Pitcher.h"
class TintinPitcher :
    public Pitcher
{
private:
public:
    TintinPitcher() :
        Pitcher(L"tintin", 20) {}

    void decideNextPitch()override;
};

