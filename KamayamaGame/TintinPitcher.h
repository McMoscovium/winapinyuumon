#pragma once
#include "Pitcher.h"
class TintinPitcher :
    public Pitcher
{
private:
public:
    TintinPitcher() :
        Pitcher(L"tintin", 30) {}

    void decideNextPitch()override;
};

