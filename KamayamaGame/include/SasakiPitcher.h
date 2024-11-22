#pragma once
#include "Pitcher.h"
class SasakiPitcher :
    public Pitcher
{
private:
public:
    SasakiPitcher() :
        Pitcher(L"²X–Ø˜NŠó", 30) {}

    void decideNextPitch()override;
};

