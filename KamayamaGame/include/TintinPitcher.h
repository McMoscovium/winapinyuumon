#pragma once
#include "Pitcher.h"
class TintinPitcher :
    public Pitcher
{
private:
public:
    TintinPitcher() :
        Pitcher(
            L"tintin",
            20, 34,
            L".//assets//投手スプライトシート.bmp",
            SIZE{168,266}
        ) {}

    void decideNextPitch()override;
};

