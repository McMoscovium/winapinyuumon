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
            L".//assets//����X�v���C�g�V�[�g.bmp",
            SIZE{168,266}
        ) {}

    void decideNextPitch()override;
};

