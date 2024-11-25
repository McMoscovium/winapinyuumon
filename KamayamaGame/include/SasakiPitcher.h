#pragma once
#include "Pitcher.h"

using namespace std;

class SasakiPitcher :
    public Pitcher
{
private:
    bool isOddFrame = false;
public:
    SasakiPitcher() :
        Pitcher(
            L"²X–Ø˜NŠó",
            30,
            27,
            L".//assets//²X–Ø˜NŠó.bmp",
            SIZE{200,266}
            ) {}
    void decideNextPitch()override;
    bool nextFrame()override;
};

