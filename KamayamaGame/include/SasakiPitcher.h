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
            L"���X�ؘN��",
            30,
            27,
            L".//assets//���X�ؘN��.bmp",
            SIZE{200,266}
            ) {}
    void decideNextPitch()override;
    bool nextFrame()override;
};

