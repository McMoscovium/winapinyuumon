#pragma once
#include "Pitcher.h"

using namespace std;

class SasakiPitcher :
    public Pitcher
{
private:
public:
    SasakiPitcher() :
        Pitcher(
            L"���X�ؘN��",
            30,
            25,
            L".//assets//���X�ؘN��.bmp",
            SIZE{200,266}
            ) {}
    void decideNextPitch()override;
};

