#pragma once
#include "Pitcher.h"
class SasakiPitcher :
    public Pitcher
{
private:
public:
    SasakiPitcher() :
        Pitcher(L"���X�ؘN��", 30) {}

    void decideNextPitch()override;
};

